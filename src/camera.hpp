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
        Vec3 u, v, w;          // Camera Frame Basis Vectors
        
        void initialize();
        Color ray_color(const Ray& ray, const Hittable& world, int recursive_depth);
        Ray get_ray(int x, int y) const;
        Vec3 sample_square() const;
    public:
        // Image (aspect ratio and image width)
        double aspect_ratio = 16.0 / 9.0;
        int image_width = 400;
        int num_pixel_samples = 10;  // Count the number of random samples for each pixel
        int max_depth = 10;  // Max recursive depth of `ray_color`.
        
        double vertical_fov = 90; // Vertical view angle (field of view)
        Point3 look_from = Point3(0, 0, 0);  // Camera position
        Point3 look_at = Point3(0, 0, -1);  // Camera aim
        Point3 up_vector = Vec3(0, 1, 0);  // Orthogonal Up Vector
        
        void render(const Hittable& world);
    };
};

#endif