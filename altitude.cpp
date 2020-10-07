#include <iostream>
#include <fstream>
#include <string>

#include "camera.hpp"
#include "color.hpp"
#include "entity_list.hpp"
#include "sphere.hpp"
#include "material.hpp"


entity_list random_scene() {
    entity_list world;

    auto ground_material = make_shared<lambertian>(color3(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for(int a = -11; a < 11; a++) {
        for(int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + (0.9 * random_double()), 0.2, b + (0.9 * random_double()));

            if((center - point3(4, 0.2, 0)).get_magnitude() > 0.9) {
                shared_ptr<material> sphere_material;

                if(choose_mat < 0.8) {
                    // Diffuse
                    auto albedo = color3::random() * color3::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if(choose_mat < 0.95) {
                    // Metal
                    auto albedo = color3::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material_1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material_1));

    auto material_2 = make_shared<lambertian>(color3(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material_2));

    auto material_3 = make_shared<metal>(color3(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material_3));

    return world;
}

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
    auto world = random_scene();


    /* CAMERA */
    point3 look_from(13, 2, 3);
    point3 look_at(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(look_from, look_at, vup, 20, ASPECT_RATIO, aperture, dist_to_focus);


    /* RENDER; WRITE TO FILE IN PPM FORMAT */
    out_file << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n255\n";

    for(int i = IMG_HEIGHT - 1; i >= 0; i--) {
        // Progress Indicator
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for(int j = 0; j < IMG_WIDTH; j++) {
            color3 pixel_color(0, 0, 0);
            // Anti-aliasing; get n samples in each pixel
            for(int s = 0; s < AA_SAMPLE; s++) {
                // Get random sample from inside pixel
                auto u = (j + random_double()) / (IMG_WIDTH - 1);
                auto v = (i + random_double()) / (IMG_HEIGHT - 1);
                // Get the ray from camera to those UV coordinates
                ray r = cam.get_ray(u, v);
                // After getting the ray from the camera, use ray_color to get ray's behavior in 
                // world; i.e. what objects the ray hits. Returned ray color is then added to 
                // pixel_color to color the pixel at this (i, j).
                pixel_color = operator+(pixel_color, ray_color(r, world, MAX_RAY_BOUNCE));
            }
            
            write_color(out_file, pixel_color, AA_SAMPLE);
        }
    }
    std::cerr << "\nDone.\n";

    out_file.close();
    return 0;
}