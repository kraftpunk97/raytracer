// Creating the first image.

#include <iostream>
#include <vec.hpp>
#include <color.hpp>

const int image_width = 256;
const int image_height = 256;

int main(int argc, char* argv[]) {
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i=0; i<image_height; i++) {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int j=0; j<image_width; j++) {
            auto pixel_color = rt::Color(float(j) / (image_width-1),
                                         float(i) / (image_height-1),
                                         0.0);
            rt::write_color(std::cout, pixel_color);
        }

    }    
    std::clog << "\rDone.              \n";
    return 0;
}