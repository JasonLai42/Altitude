#ifndef vector_hpp
#define vector_hpp

#include<iostream>
#include <stdlib.h>
#include <math.h>

class vec3 {
    public:
        vec3() {}
        vec3(float e0, float e1, float e2) { 
            e[0] = e0; 
            e[1] = e1; 
            e[2] = e2; 
        }

        // Position
        inline float get_x() const { return e[0]; }
        inline float get_y() const { return e[1]; }
        inline float get_z() const { return e[2]; }
        
        // Color
        inline float get_r() const { return e[0]; }
        inline float get_g() const { return e[1]; }
        inline float get_b() const { return e[2]; }

        inline const vec3& operator+() const { return *this; }
        inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        inline float operator[](int i) const { return e[i]; }
        inline float& operator[](int i) { return e[i]; };

        inline vec3& operator+=(const vec3 &v2);
        inline vec3& operator-=(const vec3 &v2);
        inline vec3& operator*=(const vec3 &v2);
        inline vec3& operator/=(const vec3 &v2);
        inline vec3& operator*=(const float t);
        inline vec3& operator/=(const float t);

        // const after function name means the function will not modify any objects i.e. can be called on const objects
        // compiler checks function will not modify any objects
        inline float get_magnitude() const {
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        inline float get_squared_magnitude() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        inline void make_unit_vector();

        float e[3];
};

inline vec3 operator+(const vec3 &v1, const vec3 &v2);

inline vec3 operator-(const vec3 &v1, const vec3 &v2);

inline vec3 operator*(const vec3 &v1, const vec3 &v2);

inline vec3 operator/(const vec3 &v1, const vec3&v2);

inline vec3 operator*(const vec3 &v, float t);

inline vec3 operator/(const vec3 &v, float t);

inline float dot(const vec3 &v1, const vec3 &v2);

inline vec3 cross(const vec3 &v1, const vec3 &v2);

inline vec3 unit_vector(vec3 v);

inline std::istream& operator>>(std::istream &is, vec3 &t);

inline std::ostream& operator<<(std::ostream &os, const vec3 &t);

#endif