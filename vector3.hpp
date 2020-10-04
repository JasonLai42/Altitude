#ifndef vector3_hpp
#define vector3_hpp

#include <iostream>

#include "constants.hpp"


using std::sqrt;

class vec3 {
    public:
        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // Components; alternatively r g b for color
        double get_x() const { return e[0]; }
        double get_y() const { return e[1]; }
        double get_z() const { return e[2]; }

        inline const vec3& operator+() const { return *this; }
        inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        inline double operator[](int i) const { return e[i]; }
        inline double& operator[](int i) { return e[i]; };

        inline vec3& operator+=(const vec3 &v2);
        inline vec3& operator-=(const vec3 &v2);
        inline vec3& operator*=(const vec3 &v2);
        inline vec3& operator/=(const vec3 &v2);
        inline vec3& operator*=(const double t);
        inline vec3& operator/=(const double t);

        // const after function name means the function will not modify any objects i.e. can be called on const objects
        // compiler checks function will not modify any objects
        inline double get_magnitude() const {
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        inline double get_squared_magnitude() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        inline void make_unit_vector();

        // Vec3 random utility functions; generate vectors (directions) with random params
        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }
        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        double e[3];
};

/* Type aliases for vec3 */
// 3D point
using point3 = vec3;
// RGB color
using color3 = vec3;

/* vec3 CLASS FUNCTIONS */
inline vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3& vec3::operator/=(const double t) {
    double k = 1.0 / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline void vec3::make_unit_vector() {
    double k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

/* AUXILIARY FUNCTIONS FOR vec3 */
inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

// Multiply the elements (not the same as dot product)
inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3&v2) {
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3 &v, double t) {
    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline double dot(const vec3 &v1, const vec3 &v2) {
    return (v1.e[0] * v2.e[0]) + (v1.e[1] * v2.e[1]) + (v1.e[2] * v2.e[2]);
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
                (v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2]),
                (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline vec3 unit_vector(vec3 v) {
    return operator/(v, v.get_magnitude());
}

inline std::istream& operator>>(std::istream &in, vec3 &v) {
    in >> v.e[0] >> v.e[1] >> v.e[2];
    return in;
}

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    out << v.e[0] << " " << v.e[1] << " " << v.e[2];
    return out;
}

// See if random point is in unit sphere
/* Used for Vassillen Chizhov Lambertian approximation of diffuse surfaces
 * When ray strikes diffuse surface, we take the unit normal at the hit point and construct a 
 * UNIT sphere that is tanget to surface at the hit point with center at tip of unit normal. 
 * Pick a random point in this sphere, that is where the ray will bounce to off the hit point.
 */
vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1, 1);
        if(p.get_squared_magnitude() >= 1)
            continue;

        return p;
    }
}

/* Used for estimating True Lambertian Reflection, by picking points on the surface of the UNIT
 * sphere tanget to the surface at the hit point with center at tip of unit normal. Reflected 
 * rays will instead go to these points on the surface of the sphere.
 */
vec3 random_unit_vector() {
    auto a = random_double(0, 2 * PI);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - (z * z));

    return vec3(r * cos(a), r * sin(a), z);
}

/* Scatters rays from the hit point away with no dependence on the angle from the normal.
 * Another way of doing diffuse surfaces, but rays can go anywhere.
 */
vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0) // In same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

#endif