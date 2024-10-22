#include <iostream>
#include "camera.hpp"

namespace rt {

    void Camera::initialize() {
        // Calculate the image height, and ensure it's atleast 1.
        image_height = std::fmax(1.0, image_width/aspect_ratio);
        camera_center = rt::Point3(0, 0, 0);
        
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = image_width * (viewport_height/image_height);

        auto viewport_x = rt::Vec3(viewport_width, 0, 0);  // Vector across the viewport
        auto viewport_y = rt::Vec3(0, -viewport_height, 0);  // Vector down the viewport

        pixel_x_delta = viewport_x / image_width;  
        pixel_y_delta = viewport_y / image_height;

        // Calculate the position of the upper left pixel
        auto viewport00 = camera_center - viewport_x/2 - viewport_y/2
                        - rt::Vec3(0, 0, focal_length);
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

    Color Camera::ray_color(const Ray& ray, const Hittable& world) {
        rt::HitRecord record;
        if (world.hit(ray, rt::Interval(0.0, rt::inf), record)) {
            auto direction = random_on_hemisphere(record.normal);
            return 0.5 * ray_color(Ray(record.p,direction), world);
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