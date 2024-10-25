#include <iostream>
#include "camera.hpp"
#include "material.hpp"

namespace rt {

    void Camera::initialize() {
        // Calculate the image height, and ensure it's atleast 1.
        image_height = std::fmax(1.0, image_width/aspect_ratio);
        camera_center = look_from;
        
        auto focal_length = (look_from-look_at).length();
        auto theta = deg2rad(vertical_fov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2 * h * focal_length;
        auto viewport_width = image_width * (viewport_height/image_height);

        w = unit_vector(look_from - look_at);  // Towards the object
        u = unit_vector(cross(up_vector, w));
        v = cross(w, u);

        auto viewport_x = viewport_width  *  u;  // Vector across the viewport
        auto viewport_y = viewport_height * -v;  // Vector down the viewport

        pixel_x_delta = viewport_x / image_width;  
        pixel_y_delta = viewport_y / image_height;

        // Calculate the position of the upper left pixel
        auto viewport00 = camera_center - viewport_x/2 - viewport_y/2
                        - (focal_length*w);
        pixel00_loc = viewport00 + (pixel_x_delta+pixel_y_delta)/2;  // I guess the pixel is at the center of the viewport cell.
    }

    Ray Camera::get_ray(int x, int y) const {
        // Construct a camera originating from the origin and directed at randomly sampled 
        // point around the location (x, y).

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + (x+offset.x())*pixel_x_delta
                                        + (y+offset.y())*pixel_y_delta;

        auto ray_direction = pixel_sample - camera_center;

        return Ray(camera_center, ray_direction);

    }

    Vec3 Camera::sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5] -> [.5,.5] unit sqaure
        return Vec3(random_double()-0.5, random_double()-0.5, 0);
    }

    Color Camera::ray_color(const Ray& ray, const Hittable& world, int recursive_depth=0) {
        // If we've exceeded the max recursive depth, gather no more light.
        if (recursive_depth > max_depth) { return Color(0, 0, 0); }

        rt::HitRecord record;
        if (world.hit(ray,rt::Interval(0.001,rt::inf), record)) {
            Color attenuation;
            Ray ray_scattered;
            if (record.mat->scatter(ray, record, attenuation, ray_scattered)) {
                return attenuation * ray_color(ray_scattered, world, recursive_depth+1);
            }
            return Color(0, 0, 0);
        }
        
        // Background

        // Find unit vector in the direction of the ray
        auto unit_direction = rt::unit_vector(ray.direction());
        
        // Linearly scale the blue
        auto a = 0.5*(unit_direction.y() + 1.0); // -1<=y<=1 => 0<=y+1<=2 => 0<=0.5(y+1)<=1 
        return (1.0-a)*rt::Color(1.0, 1.0, 1.0) + a*rt::Color(0.5, 0.7, 1.0);
    }

    void Camera::render(const Hittable& world) {
        initialize();

        // Render
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int y=0; y<image_height; y++) {
            std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
            for (int x=0; x<image_width; x++) {;
                Color pixel_color = Color(0, 0, 0);
                for (int i=0; i<num_pixel_samples; i++) {
                    Ray ray = get_ray(x, y);

                    pixel_color += ray_color(ray, world)/num_pixel_samples;    
                }
                write_color(std::cout, pixel_color);
            }
        }    
        std::clog << "\rDone.              \n";
    }
};