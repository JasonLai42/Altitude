#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include "constants.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "entity_list.hpp"
#include "sphere.hpp"


// RNG for real number >= 0 and < 1
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    
    return distribution(generator);
}

color3 ray_color(const ray& r, const entity& world) {
    hit_record rec;
    // Check for hits
    if(world.hit(r, 0, INF, rec)) {
        return operator*(operator+(rec.normal, color3(1, 1, 1)), 0.5);
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


    /* WORLD */
    entity_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


    /* CAMERA */
    camera cam;


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
                pixel_color = operator+(pixel_color, ray_color(r, world));
            }
            
            write_color(out_file, pixel_color, AA_SAMPLE);
        }
    }
    std::cerr << "\nDone.\n";

    out_file.close();
    return 0;
}