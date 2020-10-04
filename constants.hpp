#ifndef constants_hpp
#define constants_hpp

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

#include "pcg32.hpp"


/* FOR RNG PURPOSES */
pcg32 rng;

/* USINGS */
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

/* UNIVERSAL CONSTANTS */
#define INF (std::numeric_limits<double>::infinity())
#define PI 3.1415926535897932385

/* UTILITY FUNCTIONS */
// Convert degrees to radians
inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}
// RNG for real number >= 0 and < 1
inline double random_double() {
    return rng.nextDouble();
}
inline double random_double(double min, double max) {
    return min + ((max - min) * rng.nextDouble());
}
// Clamps a value to a range (if value is outside range and lower than min, we take min; vice versa)
inline double clamp(double x, double min, double max) {
    if(x < min)
        return min;
    if(x > max)
        return max;
    return x;
}

/* IMAGE RESOLUTION */
#define ASPECT_RATIO (16.0 / 9.0)
#define IMG_WIDTH 1200
#define IMG_HEIGHT (static_cast<int>(IMG_WIDTH / ASPECT_RATIO))

/* VIEWPORT DIMENSIONS */
#define VWPORT_HEIGHT 2.0
#define VWPORT_WIDTH (ASPECT_RATIO * VWPORT_HEIGHT)
#define FOCAL_LENGTH 1.0

/* IMAGE QUALITY */
#define AA_SAMPLE 100
#define MAX_RAY_BOUNCE 50

#endif