#include "color.hpp"

namespace rt {
    
    void write_color(std::ostream& out, const Color& pixel_color) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Applying a gamma transformations
        r = linear_to_gamma(r);
        g = linear_to_gamma(g);
        b = linear_to_gamma(b);

        // Translate the double values to 8-bit ints
        static const Interval intensity(0.000, 0.999);
        int r_val = 256 * intensity.clamp(r);
        int g_val = 256 * intensity.clamp(g);
        int b_val = 256 * intensity.clamp(b);

        // Write out the pixel color components
        out << r_val << ' ' << g_val << ' ' << b_val << '\n';
    }
};