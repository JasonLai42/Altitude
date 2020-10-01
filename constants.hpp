#ifndef constants_hpp
#define constants_hpp

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

/* COMMON HEADERS */
#include "vector3.hpp"
#include "ray.hpp"


/* USINGS */
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

/* UNIVERSAL CONSTANTS */
#define INF (std::numeric_limits<double>::infinity())
#define PI 3.1415926535897932385

/* UTILITY FUNCTIONS */
inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
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

#endif