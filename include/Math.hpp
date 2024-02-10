#ifndef MATH_H
#define MATH_H

namespace Math {
    struct vec2 {
        float x, y;
        vec2();
        vec2(float x);
        vec2(float x, float y);

        vec2 operator+(vec2 other);
        vec2 operator-(vec2 other);
        vec2 operator*(float a);
        vec2 operator/(float a);
    };
    float dotProduct(vec2 a, vec2 b);
    float interpolate(float a, float b, float x);
    vec2 normalize(vec2 a);
};

#endif