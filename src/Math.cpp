#include "../include/Math.hpp"
#include <cmath>

namespace Math {
    vec2::vec2() : x(0.0f), y(0.0f) {};
    vec2::vec2(float a) : x(a), y(a) {};
    vec2::vec2(float x, float y) : x(x), y(y) {};

    vec2 vec2::operator+(vec2 other) { return vec2(x + other.x, y + other.y); }
    vec2 vec2::operator-(vec2 other) { return vec2(x - other.x, y - other.y); }
    vec2 vec2::operator*(float a) { return vec2(x * a, y * a); }
    vec2 vec2::operator/(float a) { return vec2(x / a, y / a); }

    float dotProduct(vec2 a, vec2 b) {
        return a.x * b.x + a.y * b.y;
    };

    vec2 normalize(vec2 a) {
        float length = sqrt(a.x * a.x + a.y * a.y);
        return a / length;
    }

    float interpolate(float a, float b, float x) {
        if (x < 0.0f) return a;
        if (x > 1.0f) return b;
        
        float easedX = 6*x*x*x*x*x - 15*x*x*x*x + 10*x*x*x;
        return a + (b - a) * easedX;
    }
}