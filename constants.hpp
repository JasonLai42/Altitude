#ifndef constants_hpp
#define constants_hpp

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