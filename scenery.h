#ifndef PROJECT_LOOCH_SCENERY_H
#define PROJECT_LOOCH_SCENERY_H

#include "core.h"

#include <vector>

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
    Light(double str_, double x_, double y_, double z_);
};

struct Camera {
    Point c;
    int h;
    int w;
    double rx;
    double ry;
    double rz;
    
    Camera() = default;
    Camera(double x_, double y_, double z_, int h_, int w_, double rx_, double ry_, double rz_);
    
};


struct Scene {
    std::vector<Camera> cameras;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
    Light light_d;
    double light_a;
    
    Scene () = default;
};

#endif //PROJECT_LOOCH_SCENERY_H
