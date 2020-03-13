#include <iostream>
#include "core.h"

template<typename T>
T min(T a, T b) {
    if (a < b) return a;
    return b;
}

template<typename T>
T max(T a, T b) {
    if (a > b) return a;
    return b;
}

template<typename T>
T to_range(T a, T min_, T max_) {
    return min(max_, max(min_, a));
}

double deg_to_rad(double deg) {
    return deg / 180 * PI;
}

Point::Point(double x_, double y_, double z_) {
    x = x_;
    y = y_;
    z = z_;
}

std::ostream &operator<<(std::ostream &out, Point &a) {
    out << "Point(" << a.x << "; " << a.y << "; " << a.z << ")";
    return out;
}

Point operator+(Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator*(Point a, double k) {
    return Point(a.x * k, a.y * k, a.z * k);
}

double operator*(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point operator/(Point a, double k) {
    return Point(a.x / k, a.y / k, a.z / k);
}

Point operator-(Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

Color::Color(int r_, int g_, int b_, int a_) {
    r = r_;
    g = g_;
    b = b_;
    a = a_;
}

Color mix(Color a, Color b) {
    return Color((a.r + b.r) / 2, (a.g + b.g) / 2, (a.b + b.b) / 2, 255);
}

Color operator*(Color a, double k) {
    return Color(to_range(a.r * k, 0., 255.), to_range(a.g * k, 0., 255.), to_range(a.b * k, 0., 255.), 255);
}

Color operator+(Color a, Color b) {
    return Color(to_range(a.r + b.r, 0, 255), to_range(a.g + b.g, 0, 255), to_range(a.b + b.b, 0, 255), 255);
}