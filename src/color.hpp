#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec.hpp"
#include "interval.hpp"

namespace rt {
    using Color = Vec3;

    void write_color(std::ostream& out, const Color& pixel_color);

    inline double linear_to_gamma(double linear_component) {
        return linear_component>0 ? std::sqrt(linear_component) : 0;
    }
};

#endif 