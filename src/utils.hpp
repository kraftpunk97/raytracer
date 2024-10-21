#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

namespace rt {
    // Constants
    const double inf = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;


    inline double deg2rad(double degrees) { return degrees*pi/180.0; }
};
#endif