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
        inline float x() const { return e[0]; }
        inline float y() const { return e[1]; }
        inline float z() const { return e[2]; }
        
        // Color
        inline float r() const { return e[0]; }
        inline float g() const { return e[1]; }
        inline float b() const { return e[2]; }

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
        inline float magnitude() const {
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        inline float squared_magnitude() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        inline void make_unit_vector();

        float e[3];
};

#endif