#include <iostream>
#include <fstream>
#include <string>

#include "constants.hpp"
#include "vector3.hpp"
#include "color.hpp"


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
    out_file << "P3\n" << IMG_WIDTH << " " << IMG_HEIGHT << "\n255\n";

    for(int i = IMG_HEIGHT - 1; i >= 0; i--) {
        // Progress Indicator
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for(int j = 0; j < IMG_WIDTH; j++) {
            color3 pixel_color(double(j)/(IMG_WIDTH - 1), 
                                double(i)/(IMG_HEIGHT - 1), 
                                0.25);
            
            write_color(out_file, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";

    out_file.close();
    return 0;
}