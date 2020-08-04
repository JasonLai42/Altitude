#include <iostream>
#include <fstream>
#include <string>

#include "constants.hpp"
#include "vector.hpp"

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

    for(int i = y_pos - 1; i >= 0; i--) {
        for(int j = 0; j < x_pos; j++) {
            vec3 col(static_cast<float>(j) / static_cast<float>(x_pos), 
                        static_cast<float>(i) / static_cast<float>(y_pos), 
                        0.2);

            int ir = static_cast<int>(255.99 * col[0]);
            int ig = static_cast<int>(255.99 * col[1]);
            int ib = static_cast<int>(255.99 * col[2]);
            out_file << ir << " " << ig << " " << ib << "\n";
        }
    }


    out_file.close();
    return 0;
}