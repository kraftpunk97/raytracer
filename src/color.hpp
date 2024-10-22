#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec.hpp"
#include "interval.hpp"

namespace rt {
    using Color = Vec3;

    void write_color(std::ostream& out, const Color& pixel_color);
};

#endif 