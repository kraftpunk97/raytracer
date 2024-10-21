#ifndef CAMERA_H
#define CAMERA_H

#include "color.hpp"
#include "hittable.hpp"

namespace rt {
    class Camera {
    private:
        int image_height;      // Rendered image height
        Point3 camera_center;
        Point3 pixel00_loc;    // Position of 0, 0
        Vec3 pixel_x_delta;    // Offset to the pixel on the right
        Vec3 pixel_y_delta;    // Offset to the pixel below
        
        void initialize();
        Color ray_color(const Ray& ray, const Hittable& world);
    public:
        // Image (aspect ratio and image width)
        double aspect_ratio = 16.0 / 9.0;
        int image_width = 400;
        
        void render(const Hittable& world);
    };
};

#endif