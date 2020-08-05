#include <iostream>
#include <fstream>
#include <string>

#include "constants.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "entity_list.hpp"

vec3 color(const ray& r, entity *world) {
    hit_record rec;
    if(world->hit(r, 0.0, MAXFLOAT, rec)) {
        return operator*(vec3(rec.normal.get_x() + 1, 
                                rec.normal.get_y() + 1, 
                                rec.normal.get_z() + 1), 
                                0.5);
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
    out_file << "P3\n" << x_pos << " " << y_pos << "\n255\n";

    // Start drawing image from lower left corner; camera at (0, 0, 0)
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    entity *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    entity *world = new entity_list(list, 2);

    for(int i = y_pos - 1; i >= 0; i--) {
        for(int j = 0; j < x_pos; j++) {
            float u = static_cast<float>(j) / static_cast<float>(x_pos);
            float v = static_cast<float>(i) / static_cast<float>(y_pos);
            ray r(origin, operator+(lower_left_corner, 
                            operator+(operator*(horizontal, u), 
                                operator*(vertical, v))));
            
            vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world);
            int ir = static_cast<int>(255.99 * col[0]);
            int ig = static_cast<int>(255.99 * col[1]);
            int ib = static_cast<int>(255.99 * col[2]);

            out_file << ir << " " << ig << " " << ib << "\n";
        }
    }


    out_file.close();
    return 0;
}