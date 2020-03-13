#ifndef PROJECT_LOOCH_SCENERY_H
#define PROJECT_LOOCH_SCENERY_H

#include "core.h"
#include <vector>
#include <string>
#include <fstream>

struct Sphere {
    double r;
    Point c;
    Color color;
    unsigned int shrp; // if 0 - no highlights
    double refl;
    
    Sphere() = default;
    
    Sphere(Point c_, double r_, int red_, int green_, int blue_, unsigned int shrp_, double refl_);
};

struct Light {
    double str;
    Point c;
    
    Light() = default;
    
    Light(Point c_, double str_);
};

struct Camera {
    Point c;
    int h;
    int w;
    double rx;
    double ry;
    double rz;
    double fov;
    
    Camera() = default;
    
    Camera(Point c_, int h_, int w_, double rx_, double ry_, double rz_, double FOV);
};


struct Scene {
    std::vector<Camera> cameras;
    std::vector<Sphere> spheres;
    std::vector<Light> lights_p;
    std::vector<Light> lights_d;
    double light_a;
    std::string output_file_path;
    Color background;
    
    Scene() = default;
    Scene(std::string path);
};

#endif