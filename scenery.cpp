#include "scenery.h"

Sphere::Sphere(Point c_, double r_, int red_, int green_, int blue_, unsigned int shrp_, double refl_) {
    c = c_;
    r = r_;
    color = Color(red_, green_, blue_, 255);
    shrp = shrp_;
    refl = refl_;
}

Light::Light(double str_, double x_, double y_, double z_) {
    c = Point(x_, y_, z_);
    str = str_;
}

Camera::Camera(double x_, double y_, double z_, int h_, int w_, double rx_, double ry_, double rz_) {
    c = Point(x_, y_, z_);
    h = h_;
    w_ = w_;
    rx = rx_;
    ry = ry_;
    rz = rz_;
}