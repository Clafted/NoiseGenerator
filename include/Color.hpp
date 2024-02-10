#ifndef COLOR
#define COLOR

#include <cstdint>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color() : r(0.0f), g(0.0f), b(0.0f) {};
    Color (uint8_t r, uint8_t g, uint8_t b) 
        : r(r), g(g), b(b) {};

    Color operator*(float a) {
        return Color(this->r * a, this->g * a, this->b * a);
    }

    Color operator+(Color other) {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    Color operator-(Color other) {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    Color operator+=(Color other) {
        return *this + other;
    }

    Color operator-=(Color other) {
        return *this - other;
    }
};

#endif