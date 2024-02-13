#ifndef COLOR
#define COLOR

#include <cstdint>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color() : r(0.0f), g(0.0f), b(0.0f) {};
    Color (int r, int g,  int b) 
        : r(r), g(g), b(b) 
    {
        if (r > 255) this->r = 255;
        if (r < 0) this->r  = 0;
        if (g > 255) this->g = 255;
        if (g < 0) this->g  = 0;
        if (b > 255) this->b = 255;
        if (b < 0) this->b = 0;
    };

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