//
// Created by myav on 13.03.2020.
//

#ifndef PROJECT_LOOCH_CORE_H
#define PROJECT_LOOCH_CORE_H

struct Point {
    double x, y, z;
    
    Point() = default;
    
    Point(double x_, double y_, double z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};


#endif //PROJECT_LOOCH_CORE_H
