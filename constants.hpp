#ifndef constants_hpp
#define constants_hpp

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

#include "pcg32.hpp"


/* USINGS */
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

/* FOR RNG PURPOSES */
pcg32 RNG;

/* UNIVERSAL CONSTANTS */
#define INF (std::numeric_limits<double>::infinity())
#define PI 3.1415926535897932385

/* IMAGE RESOLUTION */
#define ASPECT_RATIO (3.0 / 2.0)
#define IMG_WIDTH 1200
#define IMG_HEIGHT (static_cast<int>(IMG_WIDTH / ASPECT_RATIO))

/* IMAGE QUALITY */
#define AA_SAMPLE 500
#define MAX_RAY_BOUNCE 50

/* UTILITY FUNCTIONS */
// Convert degrees to radians
inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}
// RNG for real number >= 0 and < 1
inline double random_double() {
    return RNG.nextDouble();
}
inline double random_double(double min, double max) {
    return min + ((max - min) * RNG.nextDouble());
}
// Clamps a value to a range (if value is outside range and lower than min, we take min; vice versa)
inline double clamp(double x, double min, double max) {
    if(x < min)
        return min;
    if(x > max)
        return max;
    return x;
}

#endif