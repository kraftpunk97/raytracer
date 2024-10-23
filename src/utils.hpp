#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <iostream>
#include <random>
#include <limits>
#include <memory>

namespace rt {
    // Constants
    const double inf = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;
    const double s = 1e-8;


    inline double deg2rad(double degrees) { return degrees*pi/180.0; }

    inline double random_double(double min=0.000, double max=1.000) {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return min + (max-min)*distribution(generator);
    }
};
#endif