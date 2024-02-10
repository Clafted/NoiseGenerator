#include "../include/NoiseGenerator.hpp"
#include "../include/Math.hpp"
#include <cmath>
#include <ctime>
#include <ratio>
#include <iostream>
#include <chrono>

using namespace Math;
using namespace std::chrono;

float easedInterpolate(float a, float b, float x);

std::vector<Color> NoiseGenerator::generatePerlinNoise(int finalWidth, int finalHeight, int spacing) {
    // Generate gradients
    double theta;
    std::vector<vec2> normals((finalWidth / spacing + 1) * (finalHeight / spacing + 1));
    high_resolution_clock::time_point start = high_resolution_clock::now();
    for (int i = 0; i < normals.size(); i++) {
        srand(i + 1000000000 * duration_cast<duration<double>>(high_resolution_clock::now() - start).count());
        theta = (rand() % 360) * 3.1415 / 180.0;
        normals[i] = vec2(sin(theta), cos(theta));
    }
    vec2 tLCorner, tRCorner, bLCorner, bRCorner;
    float tL, tR, bL, bR, xI1, xI2, finalColor;
    std::vector<Color> result(finalWidth * finalHeight);
    // Traverse cells
    for (int x = 0; x < finalWidth / spacing; x++) {
        for (int y = 0; y < finalHeight / spacing; y++) {
            // Find the four corner normals
            tLCorner = normals[x + (finalWidth / spacing + 1) * y];
            tRCorner = normals[(x + 1) + (finalWidth / spacing + 1) * y];
            bLCorner = normals[x + (finalWidth / spacing + 1) * (y + 1)];
            bLCorner = normals[(x + 1) + (finalWidth / spacing + 1) * (y + 1)];
            // Traverse pixels
            for (int x2 = 0; x2 < spacing; x2++) {
                for (int y2 = 0; y2 < spacing; y2++) {
                    // Calculate dot-products with four corners
                    tL = dotProduct(vec2(x2, y2) / spacing, tLCorner);
                    tR = dotProduct(vec2(x2 - spacing, y2) / spacing, tRCorner);
                    bL = dotProduct(vec2(x2, y2 - spacing) / spacing, bLCorner);
                    bR = dotProduct(vec2(x2 - spacing, y2 - spacing) / spacing, bRCorner);
                    // Interpolate values
                    xI1 = easedInterpolate(tL, tR, (float) x2 / (float) (spacing - 1));
                    xI2 = easedInterpolate(bL, bR, (float) x2 / (float) (spacing - 1));
                    finalColor = (easedInterpolate(xI1, xI2, (float)y2 / (float) (spacing - 1)) + 1.0) / 2.0f;

                    result[(x * spacing) + x2 + ((y * spacing) + y2) * (finalWidth)] = Color(255, 255, 255) * finalColor;
                }
            }
        }
    }

    return result;
}

float easedInterpolate(float a, float b, float x)
{
    float easedX = 6*x*x*x*x*x - 15*x*x*x*x + 10*x*x*x;
    return a + (b - a) * easedX;
}