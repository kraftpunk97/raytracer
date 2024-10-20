#include "color.hpp"

namespace rt {
    
    void write_color(std::ostream& out, const Color& pixel_color) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Translate the double values to 8-bit ints
        int r_val = 255.999 * r;
        int g_val = 255.999 * g;
        int b_val = 255.999 * b;

        // Write out the pixel color components
        out << r_val << ' ' << g_val << ' ' << b_val << '\n';
    }
};