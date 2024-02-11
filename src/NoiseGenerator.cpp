#include "../include/NoiseGenerator.hpp"
#include "../include/Math.hpp"
#include <cmath>
#include <ctime>
#include <ratio>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace Math;
using namespace std::chrono;

std::vector<float> NoiseGenerator::generatePerlinNoise(int finalWidth, int finalHeight, int spacing, int intervals) {
    if (intervals <= 0) return std::vector<float>(finalWidth*finalHeight);
    // Generate gradients
    double theta;
    std::vector<vec2> normals((finalWidth / spacing + 1) * (finalHeight / spacing + 1));
    high_resolution_clock::time_point start = high_resolution_clock::now();
    for (int i = 0; i < normals.size(); i++) {
        srand(1000000000 * duration_cast<duration<double>>(high_resolution_clock::now() - start).count());
        theta = (rand() % 360)*3.1415 / 180.0;
        normals[i] = vec2(sin(theta), cos(theta));
    }
    std::shuffle(normals.begin(), normals.end(), std::default_random_engine(rand()));
    // Calculate pixel colors
    vec2 g0, g1, g2, g3;
    float dot0, dot1, dot2, dot3;
    float xI1, xI2, finalColor;
    std::vector<float> result(finalWidth*finalHeight);
    // Traverse cells
    for (int gX = 0; gX < finalWidth/spacing; gX++) {
        for (int gY = 0; gY < finalHeight/spacing; gY++) {
            // Find the four corner normals
            g0 = normals[(finalWidth/spacing + 1)*gY + gX];
            g1 = normals[(finalWidth/spacing + 1)*gY + gX+1];
            g2 = normals[(finalWidth/spacing + 1)*(gY+1) + gX];
            g3 = normals[(finalWidth/spacing + 1)*(gY+1) + gX+1];
            // Traverse pigxels
            for (int x = 0; x < spacing; x++) {
                for (int y = 0; y < spacing; y++) {
                    // Calculate dot-products with four corners
                    dot0 = dotProduct(vec2(x, y) / (spacing-1.0), g0);
                    dot1 = dotProduct(vec2(x-spacing, y) / (spacing-1.0), g1);
                    dot2 = dotProduct(vec2(x, y-spacing) / (spacing-1.0), g2);
                    dot3 = dotProduct(vec2(x-spacing, y-spacing) / (spacing-1.0), g3);
                    // Interpolate values
                    xI1 = interpolate(dot0, dot1, x/(spacing-1.0));
                    xI2 = interpolate(dot2, dot3, x/(spacing-1.0));
                    finalColor = (interpolate(xI1, xI2, y/(spacing-1.0)) + 0.65) / 1.3;

                    result[(gY*spacing + y)*finalWidth + gX*spacing + x] = finalColor;
                }
            }
        }
    }
    std::vector<float> previousIntervals = generatePerlinNoise(finalWidth, finalHeight, spacing / 2, intervals - 1);
    for (int i = 0; i < result.size(); i++) {
        result[i] = previousIntervals[i] * ((float) (intervals-1)/intervals) + result[i] * (1.0/intervals);
    }

    return result;
}