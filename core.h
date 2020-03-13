#ifndef PROJECT_LOOCH_CORE_H
#define PROJECT_LOOCH_CORE_H

#include <iostream>

const long double PI = 3.1415926535897932384626433832795;

struct Point {
    double x, y, z;
    
    Point() = default;
    Point(double x_, double y_, double z_);
};

std::ostream &operator<<(std::ostream &out, Point &a);
Point operator+(Point a, Point b);
Point operator*(Point a, double k);
double operator*(Point a, Point b);
Point operator/(Point a, double k);

Point operator-(Point a, Point b);


struct Color {
    int r, g, b, a;
    
    Color() = default;
    
    Color(int r_, int g_, int b_, int a_);
};

Color mix(Color a, Color b);

Color operator*(Color a, double k);

Color operator+(Color a, Color b);

double deg_to_rad(double deg);

template<typename T>
T to_range(T a, T min_, T max_);

template<typename T>
T min(T a, T b);

template<typename T>
T max(T a, T b);

#endif //PROJECT_LOOCH_CORE_H
