/**
 * This is a program to generate noise into a photo with the
 * dimensions specified in the BmpInfoHeader struct.
 * 
 * NOTE: The image generation structs and functions
 * (as commented below) are taken from a post on dev.to.
 * The link to the original code is here:
 * 
 * https://dev.to/muiz6/c-how-to-write-a-bitmap-image-from-scratch-1k6m
 * 
 * The Noise Generation portion of the program was programmed
 * by me however.
 * 
 * @author Noah Perez
 */

#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>
#include <vector>

// CODE FROM dev.to POST (LINK IS ABOVE ^^^)
// ----------------------------------------------------------------------

// Metadata, size of 40 bytes
struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 64; // in pixels
    int32_t height = 64; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;

    void save_on_file(std::ofstream& fout) {
        fout.write((char*)&this->sizeOfThisHeader, sizeof(uint32_t));
        fout.write((char*)&this->width, sizeof(int32_t));
        fout.write((char*)&this->height, sizeof(int32_t));
        fout.write((char*)&this->numberOfColorPlanes, sizeof(uint16_t));
        fout.write((char*)&this->colorDepth, sizeof(uint16_t));
        fout.write((char*)&this->compressionMethod, sizeof(uint32_t));
        fout.write((char*)&this->rawBitmapDataSize, sizeof(uint32_t));
        fout.write((char*)&this->horizontalResolution, sizeof(int32_t));
        fout.write((char*)&this->verticalResolution, sizeof(int32_t));
        fout.write((char*)&this->colorTableEntries, sizeof(uint32_t));
        fout.write((char*)&this->importantColors, sizeof(uint32_t));
    }
} bmpInfoHeader;

// Metadata size of 14 bytes (look at variable types)
struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54 + bmpInfoHeader.width * bmpInfoHeader.height * 3;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;

    void save_on_file(std::ofstream& fout) {
        fout.write(this->bitmapSignatureBytes, 2);
        fout.write((char*)&this->sizeOfBitmapFile, sizeof(uint32_t));
        fout.write((char*)&this->reservedBytes, sizeof(uint32_t));
        fout.write((char*)&this->pixelDataOffset, sizeof(uint32_t));
    }
} bmpHeader;

struct Pixel {
    uint8_t r = 2;
    uint8_t g = 2;
    uint8_t b = 200;

    void save_on_file(std::ofstream& fout) {
        fout.write((char*)&this->b, sizeof(uint8_t));
        fout.write((char*)&this->g, sizeof(uint8_t));
        fout.write((char*)&this->r, sizeof(uint8_t));
    }
} pixel;
// ----------------------------------------------------------------------

struct vec2 {
    float x;
    float y;

    vec2() : x(0), y(0) {};
    vec2(float x, float y) 
        : x(x), y(y) {};

    vec2 operator+(vec2 other) {
        return vec2(this->x + other.x, this->y + other.y);
    }

    template <typename T>
    vec2 operator+(T other) {
        return vec2(this->x + other, this->y + other);
    }

    vec2 operator-(vec2 other) {
        return vec2(this->x - other.x, this->y - other.y);
    }

    template <typename T>
    vec2 operator-(T other) {
        return vec2(this->x - other, this->y - other);
    }

    template <typename T>
    vec2 operator*(T other) {
        return vec2(this->x * other, this->y * other);
    }

    template <typename T>
    vec2 operator/(T other) {
        return vec2(this->x / other, this->y / other);
    }
};

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
};

Color *generatePerlinNoise(int width, int height, int spacing);

int main() {
    std::cout << "Generating noise...\n";

    Color* perlinNoise = generatePerlinNoise(bmpInfoHeader.width, bmpInfoHeader.height, 8);

    // Image generation code (also from dev.to post)
    // ----------------------------------------------------------------------
    std::ofstream fout("../../output7.bmp", std::ios::binary);
    
    bmpHeader.save_on_file(fout);
    bmpInfoHeader.save_on_file(fout);
    size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
    for (int i = 0; i < numberOfPixels; i++) {
        pixel.r = perlinNoise[i].r;
        pixel.g = perlinNoise[i].g;
        pixel.b = perlinNoise[i].b;
        pixel.save_on_file(fout);
    }
    fout.close();
    // ----------------------------------------------------------------------

    std::cout << "Completed Image Generation";
    return 0;
}

vec2 normalize(vec2 target) {
    float length = std::sqrt((target.x * target.x) + (target.y * target.y));
    return vec2(target.x / length, target.y / length);
}

float dot(vec2 a, vec2 b) {
    return (a.x * b.x) + (a.y * b.y);
}

float interpolate(float a, float b, float x) {
    if (x < 0.0f) return a;
    if (x > 1.0f) return b;
    return a + (b - a) * x;
}

Color *generatePerlinNoise(int width, int height, int spacing) {
    std::vector<vec2> gradients(((width / spacing) + 1) * ((height / spacing) + 1));
    std::vector<Color> result(width * height);

    // Create random gradients with equal spacing
    for (int i = 0; i < gradients.size(); i++) {
        gradients[i] = normalize(vec2((rand() % 1000) - 500, (rand() % 1000) - 500));
    }
    vec2 targetPoint;
    vec2 closestGradient;
    vec2 directionToTarget;
    int gX, gY, closestGradientIndex;
    float colorValue;
    for (int i = 0; i < width * height; i++) {
        targetPoint.x = i % width;
        targetPoint.y = i / width;
        // Determine coordinates and index of gradient nearest the target
        gX = (int)(targetPoint.x + (spacing / 2)) / spacing;
        gY = (int)(targetPoint.y + (spacing / 2)) / spacing;
        closestGradientIndex = gX + (gY * width / spacing);
        closestGradient = vec2(gX, gY) * spacing;
        // Calculate dot-product between vector to target and closest gradient
        directionToTarget = normalize(targetPoint - closestGradient);
        colorValue = (dot(directionToTarget, gradients[closestGradientIndex]) + 1) / 2.0f;
        // Convert colorValue into a greyscale color
        result[i] = Color(255.0f, 255.0f, 255.0f) * colorValue;
    }
    // Bilinear Interpolation
    // -----------------------------------------------

    return &result[0];
}