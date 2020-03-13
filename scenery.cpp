#include "scenery.h"

Sphere::Sphere(Point c_, double r_, int red_, int green_, int blue_, unsigned int shrp_, double refl_) {
    c = c_;
    r = r_;
    color = Color(red_, green_, blue_, 255);
    shrp = shrp_;
    refl = refl_;
}

Light::Light(Point c_, double str_) {
    c = c_;
    str = str_;
}

Camera::Camera(Point c_, int h_, int w_, double rx_, double ry_, double rz_, double FOV) {
    c = c_;
    h = h_;
    w_ = w_;
    rx = rx_;
    ry = ry_;
    rz = rz_;
    fov = FOV;
}

Scene::Scene(std::string path) {
    // TODO
}