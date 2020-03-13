#ifndef IT_GEOMETRIES_H
#define IT_GEOMETRIES_H

#include "bits/stdc++.h"
//#include "Rationals.h"
#include "tgaimage.cpp"

#define PI 3.1415926535897932384626433832795
using namespace std;

struct Point {
    double x, y, z;
    
    Point() = default;
    
    Point(double x_, double y_, double z_) {
        x = x_;
        y = y_;
        z = z_;
    }
    
    ostream &operator<<(ostream &out) {
        out << "Point(" << x << "; " << y << "; " << z << ")";
        return out;
    }
    
    Point operator+(Point b) {
        return Point(x + b.x, y + b.y, z + b.z);
    }
    
    Point operator*(double k) {
        return Point(x * k, y * k, z * k);
    }
    
    double operator*(Point b) {
        return x * b.x + y * b.y + z * b.z;
    }
    
    Point operator/(double k) {
        return Point(x / k, y / k, z / k);
    }
    
    Point operator-(Point b) {
        return Point(x - b.x, y - b.y, z - b.z);
    }
};

struct Camera {
    Point c;
    int h;
    int w;
    double rx;
    double ry;
    double rz;
    
    Camera () = default;
    
    Camera (double x_, double y_, double z_, int h_, int w_, double rx_, double ry_, double rz_) {
        c = Point(x_, y_, z_);
        h = h_;
        w_ = w_;
        rx = rx_;
        ry = ry_;
        rz = rz_;
    }
    
};

struct Sphere {
    double r;
    Point c;
    TGAColor color;
    unsigned int shrp; // if 0 - no highlights
    double refl;
    
    Sphere() = default;
    
    Sphere(Point c_, double r_, int red_, int green_, int blue_, unsigned int shrp_, double refl_) {
        c = c_;
        r = r_;
        color = TGAColor(red_, green_, blue_, 255);
        shrp = shrp_;
        refl = refl_;
    }
};

struct Light {
    double str;
    Point c;
    
    Light() = default;
    
    Light(double str_, double x_, double y_, double z_) {
        c = Point(x_, y_, z_);
        str = str_;
    }
};

// ================================= Scene =================================

struct Scene {
    vector<Camera> cameras;
    vector<Sphere> spheres;
    vector<Light> lights;
    Light light_d;
    double light_a;
    
    Scene () = default;
};

vector<Sphere>
        spheres = {
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
// =========================================================================

#endif