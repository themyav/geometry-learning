#include <vector>
#include <iostream>

#include "core.h"
#include "scenery.h"
//#include "pngimage.h"
#include "tgaimage.cpp"

#define RGB_MODE 1
#define COS_MODE 2
#define DEPTH_MODE 3
#define LIGHT_MODE 4
#define NORM_MODE 5
#define REFL_MODE 6

#define MAX_BOUNCES 3

using namespace std;

// ============================ Global variables ============================
Point cam = Point(0, 0, 0);

double d = 1.;
double FOV_h = 60;
double FOV_v = 35;

int width;
int height;

TGAColor BACKGROUND_COLOR = TGAColor(160, 160, 160, 255);

vector<Sphere> spheres = {
        //      x   y      z  rad    r    g    b  shrp  refl
        Sphere(Point(10, -3, -1), 0.5, 0, 255, 255, 20, 0.3),
        Sphere(Point(15, 5, 0), 2, 255, 0, 255, 100, 0),
        Sphere(Point(15, 1, 0), 1, 0, 0, 255, 25, 0.15),
        Sphere(Point(25, -6, 1), 3, 255, 255, 0, 15, 0.7),
        Sphere(Point(8, -2, 1), 0.5, 0, 255, 0, 75, 0),
        //Sphere(0, 0, -1005, 999, 255, 255, 255, 30, 1)
};

vector<Light> lights_p = {
        //Light(0.4, 3, -3, 10)
};
Light light_d = Light(0.7, -1, 3, 3); // Directional light
double light_a = 0; // Ambient light

// ============================== Low functions =============================
double len(Point a) {
    return sqrt(a * a);
}

double get_cos(Point a, Point b) {
    double cos_ = (a * b) / (len(a) * len(b));
    double cos_ranged = to_range(cos_, (double) 0., (double) 1.);
    //if (cos_ranged != cos_) cout << cos_ << " " << cos_ranged << "\n";
    return cos_ranged;
}

Point get_normal(Sphere sphere, Point here) {
    Point norm = Point(here.x - sphere.c.x, here.y - sphere.c.y, here.z - sphere.c.z);
    norm = norm / len(norm);
    return norm;
}

Point reflect(Point N, Point a) {
    Point b = (N * ((N * a) / len(N))) * 2. - a;
    return b;
}

// ============================= High functions =============================
pair<int, double> ray_to_sphere(Point o, Point dir) {
    double a = dir * dir;
    double t_min = 1000000;
    int i_hit = -1;
    for (int i = 0; i < spheres.size(); i++) {
        Sphere sphere = spheres[i];
        sphere.c.x -= o.x;
        sphere.c.y -= o.y;
        sphere.c.z -= o.z;
        double b = 2 * (dir * sphere.c);
        double c = (sphere.c * sphere.c) - sphere.r * sphere.r;
        vector<double> t = {};
        double d = b * b - 4 * a * c;
        if (d < 0) continue;
        if (d > 0) t = {(-b - sqrt(d)) / (-2 * a), (-b + sqrt(d)) / (-2 * a)};
        if (d == 0) t = {-b / (-2 * a)};
        for (double t_i: t) {
            if (t_i < t_min && t_i > 0) {
                t_min = t_i;
                i_hit = i;
            }
        }
    }
    t_min -= 0.0005;
    return make_pair(i_hit, t_min);
}

pair<double, double> get_lightning(Point here, Sphere sphere) {
    double here_light_d = light_a;
    double here_light_s = 0;
    Point norm = get_normal(sphere, here);
    Point toLight = light_d.c - here;
    if (ray_to_sphere(here, toLight).first == -1) {
        here_light_d += light_d.str * get_cos(norm, toLight - norm);
        if (sphere.shrp != 0) {
            here_light_s += light_d.str * pow(get_cos(here * -1., reflect(norm, toLight)), sphere.shrp);
        }
    }

    for (auto i : lights_p) {
        Point toLight = i.c - here;
        pair<int, double> result = ray_to_sphere(here, toLight);
        if (result.first == -1 || result.second >= len(toLight)) {
            // diffuse
            here_light_d += i.str * get_cos(norm, toLight - norm);
            // specular
            if (sphere.shrp != 0) {
                here_light_s += i.str * pow(get_cos(here * -1., reflect(norm, toLight)), sphere.shrp);
            }
        }
    }

    return make_pair(to_range(here_light_d, 0., 1.), to_range(here_light_s, 0., 1.));
}

TGAColor get_color(Point here, Sphere sphere, unsigned int bounces) {
    if (bounces <= 0) return BACKGROUND_COLOR;
    auto result = get_lightning(here, sphere);
    double here_light_d = result.first, here_light_s = result.second;
    // DO REFLECTION
    TGAColor here_color_d;
    if (sphere.refl != 0) {
        int i_hit_r;
        Point dir_r = reflect(get_normal(sphere, here), here * -1.);
        pair<int, double> res = ray_to_sphere(here, dir_r);
        i_hit_r = res.first;
        double k = sphere.refl;
        if (i_hit_r != -1) {
            here = here + (dir_r * res.second);
            TGAColor refl = get_color(here, spheres[i_hit_r], bounces - 1);
            here_color_d = mix(refl * k, sphere.color * (1 - k));
        } else here_color_d = mix(BACKGROUND_COLOR * k, sphere.color * (1 - k));
    } else here_color_d = sphere.color;
    here_color_d = here_color_d * here_light_d;

    double one_minus_a0 = 1 - here_light_s;
    double here_d_r = here_color_d.r / 255.;
    double here_d_g = here_color_d.g / 255.;
    double here_d_b = here_color_d.b / 255.;
    // a0 = here_light_s, a1 = 1
    double here_r = (one_minus_a0 * here_d_r + here_light_s);
    double here_g = (one_minus_a0 * here_d_g + here_light_s);
    double here_b = (one_minus_a0 * here_d_b + here_light_s);
    return TGAColor(here_r * 255, here_g * 255, here_b * 255, 255);

}

void render(char out_path[], unsigned char mode) {
    Point A = Point(d, -tan(deg_to_rad(FOV_h)) * d, tan(deg_to_rad(FOV_v)) * d);
    Point B = Point(d, tan(deg_to_rad(FOV_h)) * d, tan(deg_to_rad(FOV_v)) * d);
    Point D = Point(d, -tan(deg_to_rad(FOV_h)) * d, -tan(deg_to_rad(FOV_v)) * d);
    // rotate ABD here

    double deltaX = (B.x - A.x) / width;
    double deltaY = (B.y - A.y) / width;
    double deltaZ = (A.z - D.z) / height;
    TGAImage image(width, height, TGAImage::RGBA);
    for (int w_canvas = 0; w_canvas < width; w_canvas++) {
        for (int h_canvas = 0; h_canvas < height; h_canvas++) {
            Point dir = Point(A.x + deltaX * w_canvas, A.y + deltaY * w_canvas, A.z - deltaZ * h_canvas);
            auto checked = ray_to_sphere(cam, dir);
            int i_hit = checked.first;
            double t = checked.second;
            TGAColor here_color;
            if (i_hit != -1) {
                Point here = Point(t * dir.x, t * dir.y, t * dir.z);
                switch (mode) {
                    case RGB_MODE: {
                        // BEFORE USING COLOR - REFLECT RAY
                        // if lightning is not 0
                        here_color = get_color(here, spheres[i_hit], MAX_BOUNCES);
                        break;
                    }
                    case LIGHT_MODE: {
                        auto here_light = get_lightning(here, spheres[i_hit]);
                        here_color = TGAColor(here_light.first * 255, here_light.second * 255, 0, 255);
                        break;
                    }
                    case NORM_MODE: {
                        Point norm = get_normal(spheres[i_hit], here);
                        here_color = TGAColor((norm.x + 1) * 127, (norm.y + 1) * 127, (norm.z + 1) * 127, 255);
                        break;
                    }
                    case COS_MODE: {
                        // NOT WORKING, NOT NEEDED
                        Point norm = get_normal(spheres[i_hit], here);
                        Point toLight = light_d.c - here;
                        double cos = get_cos(norm, toLight - norm);
                        here_color = TGAColor(cos * 255, cos * 255, cos * 255, 255);
                    }
                    case DEPTH_MODE: {
                        here_color = TGAColor(t, t, t, 255);
                        break;
                    }
                    case REFL_MODE: {
                        Point norm = get_normal(spheres[i_hit], here);
                        Point refl = reflect(norm, here * -1. / len(here));
                        here_color = TGAColor((refl.x + 1) * 127, (refl.y + 1) * 127, (refl.z + 1) * 127, 255);
                        break;
                    }
                }
            } else if (mode == RGB_MODE) {
                here_color = BACKGROUND_COLOR;
            } else {
                here_color = TGAColor(0, 0, 0, 0);
            }
            image.set(w_canvas, h_canvas, here_color);
        }
    }
    image.write_tga_file(out_path);
}

int main(int argc, char *argv[]) {
    // argv: width, height, out filename
    if (argc != 3) {
        cerr << "Argument error: Got " << argc - 1 << ", expected 2";
        return 1;
    }
    ios_base::sync_with_stdio(false);
    width = 1920;
    height = 1080;
    render("C:\\Users\\Chechevatov\\Desktop\\output_rgb.tga", RGB_MODE);

    //width /= 10;
    //height /= 10;

    //render("C:\\Users\\Chechevatov\\Desktop\\output_cos.tga", COS_MODE);
    //render("C:\\Users\\Chechevatov\\Desktop\\output_depth.tga", DEPTH_MODE);
    //render("C:\\Users\\Chechevatov\\Desktop\\output_light.tga", LIGHT_MODE);
    //render("C:\\Users\\Chechevatov\\Desktop\\output_norm.tga", NORM_MODE);
    //render("C:\\Users\\Chechevatov\\Desktop\\output_refl.tga", REFL_MODE);
    return 0;
}

/*
     In space:
              +Z  +X
              |  /
              | /
              |/
  -Y ---------O---------- +Y
             /|
            / |
           /  |
         -X   -Z

     In viewport:
      A *---------------* B
        |               |
        |       * O     |
        |               |
      D *---------------* C

     On canvas:
     O *-------------- X
       |
       |
       Y
    */
