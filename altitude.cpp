#include <iostream>

int main() {
    int x_pos = 200;
    int y_pos = 100;
    std::cout << "P3\n" << x_pos << " " << y_pos << "\n255\n";

    for(int i = y_pos - 1; i >= 0; i--) {
        for(int j = 0; i < x_pos; i++) {
            float r = static_cast<float>(j) / static_cast<float>(x_pos);
            float g = static_cast<float>(i) / static_cast<float>(y_pos);
            float b = 0.2;

            int ir = static_cast<int>(255.99 * r);
            int ig = static_cast<int>(255.99 * g);
            int ib = static_cast<int>(255.99 * b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    

    return 0;
}