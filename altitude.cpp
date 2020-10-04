#include <iostream>
#include <fstream>
#include <string>

#include "camera.hpp"
#include "color.hpp"
#include "entity_list.hpp"
#include "sphere.hpp"
#include "material.hpp"


// Returns color of ray that passes through world and hits objects; depth limits recursive calls 
// to prevent blowing the stack
color3 ray_color(const ray& r, const entity& world, int depth) {
    hit_record rec;

    // If we've reached maximum allowed ray bounces, gather no more light
    if(depth <= 0) 
        return color3(0, 0, 0);

    // Check for hits
    // 0.001 to fix shadow acne; rays hitting objects not at t = 0 due to floating point 
    // approximation are ignored 
    if(world.hit(r, 0.001, INF, rec)) {
        ray scattered;
        color3 attenuation;

        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);

        return color3(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.get_direction());
    auto t = 0.5 * (unit_direction.get_y() + 1.0);
    
    // Linearly interpolate background color for gradient
    return (operator*(color3(1.0, 1.0, 1.0), (1.0 - t))) + (operator*(color3(0.5, 0.7, 1.0), t));
}

int main(int argc, char* argv[]) {

    /* READ IN FILE NAME AND OPEN OUTPUT FILE */
    if(argc != 2) {
        std::cerr << "ERROR: No file name given.\nUsage: ./altitude <file name>\n";
        exit(1);
    }
    
    // Create file name
    std::string file_name = argv[1];
    file_name.append(".ppm");

    // Open file for writing
    std::ofstream out_file;
    out_file.open(file_name, std::ios::out | std::ios::trunc);


    /* SEED RNG */
    RNG.seed(42u, 0);


    /* WORLD */
    entity_list world;
    
    auto material_ground = make_shared<lambertian>(color3(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color3(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color3(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));


    /* CAMERA */
    camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 20, ASPECT_RATIO);


    /* RENDER; WRITE TO FILE IN PPM FORMAT */
    out_file << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n255\n";

    for(int i = IMG_HEIGHT - 1; i >= 0; i--) {
        // Progress Indicator
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for(int j = 0; j < IMG_WIDTH; j++) {
            color3 pixel_color(0, 0, 0);
            // Anti-aliasing; get n samples in each pixel
            for(int s = 0; s < AA_SAMPLE; s++) {
                auto u = (j + random_double()) / (IMG_WIDTH - 1);
                auto v = (i + random_double()) / (IMG_HEIGHT - 1);
                // Get the ray from camera to those UV coordinates
                ray r = cam.get_ray(u, v);
                pixel_color = operator+(pixel_color, ray_color(r, world, MAX_RAY_BOUNCE));
            }
            
            write_color(out_file, pixel_color, AA_SAMPLE);
        }
    }
    std::cerr << "\nDone.\n";

    out_file.close();
    return 0;
}