#include <iostream>
#include <fstream>
#include <string>

#include "constants.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "entity_list.hpp"
#include "camera.hpp"
#include "material.hpp"

vec3 color(const ray& r, entity *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return operator*(attenuation, color(scattered, world, depth + 1));
        }
        else {
            return vec3(0, 0, 0);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.get_direction());
        float t = 0.5 * (unit_direction.get_y() + 1.0);
        
        return operator+(operator*(vec3(1.0, 1.0, 1.0), 1.0 - t), 
                            operator*(vec3(0.5, 0.7, 1.0), t));
    }
}

int main(int argc, char* argv[]) {

    /* READ IN FILE NAME AND OPEN OUTPUT FILE */
    if(argc != 2) {
        std::cerr << "ERROR: No file name given.\nUsage: ./altitude <file name>\n";
        exit(1);
    }
    
    std::string file_name = argv[1];
    file_name.append(".ppm");

    std::ofstream out_file;
    out_file.open(file_name, std::ios::out | std::ios::trunc);

    

    /* WRITE TO FILE IN PPM FORMAT */
    int x_pos = IMG_WIDTH;
    int y_pos = IMG_HEIGHT;
    int s_pos = IMG_HEIGHT;
    out_file << "P3\n" << x_pos << " " << y_pos << "\n255\n";

    /* ENTITIES TO GENERATE */
    entity *list[5];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
    entity *world = new entity_list(list, 5);

    /* CAMERA */
    vec3 look_from(3, 3, 2);
    vec3 look_at(0, 0, -1);
    vec3 view_up(0, 1, 0);
    float dist_to_focus = (operator-(look_from, look_at)).get_magnitude();
    float aperture = 2.0;
    camera cam(look_from, look_at, view_up, 20, static_cast<float>(x_pos) / static_cast<float>(y_pos), aperture, dist_to_focus);

    for(int i = y_pos - 1; i >= 0; i--) {
        for(int j = 0; j < x_pos; j++) {
            vec3 col(0, 0, 0);
            
            for(int k = 0; k < s_pos; k++) {
                float u = static_cast<float>(j + drand48()) / static_cast<float>(x_pos);
                float v = static_cast<float>(i + drand48()) / static_cast<float>(y_pos);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col.operator+=(color(r, world, 0));
            }

            col.operator/=(static_cast<float>(s_pos));
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = static_cast<int>(255.99 * col[0]);
            int ig = static_cast<int>(255.99 * col[1]);
            int ib = static_cast<int>(255.99 * col[2]);

            out_file << ir << " " << ig << " " << ib << "\n";
        }
    }


    out_file.close();
    return 0;
}