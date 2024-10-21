// Creating the first image.

#include "utils.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

rt::Color ray_color(const rt::Ray& ray, const rt::Hittable& world) {
    rt::HitRecord record;
    if (world.hit(ray, rt::Interval(0.0, rt::inf), record)) {
        return 0.5*(record.normal + rt::Color(1,1,1));
    }
    
    // Find unit vector in the direction of the ray
    auto unit_direction = rt::unit_vector(ray.direction());

    // Linearly scale the blue
    auto a = 0.5*(unit_direction.y() + 1.0); // -1<=y<=1 => 0<=y+1<=2 => 0<=0.5(y+1)<=1 
    return (1.0-a)*rt::Color(1.0, 1.0, 1.0) + a*rt::Color(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[]) {
    // World
    rt::HittableList world;
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,-100.5,-1), 100));
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,0,-1), 0.5));

    // Image (aspect ratio and image width)
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure it's atleast 1. 
    int image_height = std::fmax(1.0, image_width/aspect_ratio);
    
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = image_width * (viewport_height/image_height);
    auto camera_center = rt::Point3(0, 0, 0);

    auto viewport_x = rt::Vec3(viewport_width, 0, 0);  // Vector across the viewport
    auto viewport_y = rt::Vec3(0, -viewport_height, 0);  // Vector down the viewport

    auto pixel_x_delta = viewport_x / image_width;  
    auto pixel_y_delta = viewport_y / image_height;

    // Calculate the position of the upper left pixel
    auto viewport00 = camera_center - viewport_x/2 - viewport_y/2
                    - rt::Vec3(0, 0, focal_length);
    auto pixel00_loc = viewport00 + (pixel_x_delta+pixel_y_delta)/2;  // I guess the pixel is at the center of the viewport cell.

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y=0; y<image_height; y++) {
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
        for (int x=0; x<image_width; x++) {
            auto pixel_center = pixel00_loc + x*pixel_x_delta + y*pixel_y_delta;
            auto ray_direction = pixel_center - camera_center;
            rt::Ray ray = rt::Ray(camera_center, ray_direction);

            rt::Color pixel_color = ray_color(ray, world);
            rt::write_color(std::cout, pixel_color);
        }
    }    
    std::clog << "\rDone.              \n";
    return 0;
}