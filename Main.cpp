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
#include "Math.hpp"
#include "ImageGenerator.hpp"
#include "NoiseGenerator.hpp"
#include "Color.hpp"

using namespace ImageGenerator;

void generateMap(int width, int length);
void generateNoise(int width, int length, int spacing, int intervals);

int main() {
    generateNoise(1024, 1024, 512, 4);
    generateMap(1024, 1024);
    return 0;
}

void generateNoise(int width, int length, int spacing, int intervals)
{
    std::vector<float> noise = NoiseGenerator::generatePerlinNoise(width, length, spacing, intervals);
    std::vector<Color> result(width*length);
    for (int i = 0; i < result.size(); i++) {
        int lightness = ((noise[i] + 0.5f)) * 255;
        result[i] = Color(lightness, lightness, lightness);
    }
    generateImage("output/noise", width, length, result);
}

void generateMap(int width, int length) 
{
    std::cout << "Generating map...\n";
    std::vector<float> mountains = NoiseGenerator::generatePerlinNoise(width, length, 512, 2);
    std::vector<float> height = NoiseGenerator::generatePerlinNoise(width, length, 512, 4);
    std::vector<Color> island(width*length);
    // Convert shades into grass, sand, or water
    for (int i = 0; i < height.size(); i++) {
        mountains[i] = ((1 - (0.18f * (2 * (log2(std::abs(mountains[i] / 0.5f)) + 0.02f)) + 0.85f)) * 0.6f + (height[i] / 0.3f) * 0.4f);
        if (mountains[i] <= 0.27f) {
            island[i] = Color(40 * mountains[i], 100 * mountains[i], 110 * mountains[i]);
        } else {
            island[i] = Color((1.32f * (mountains[i] - 0.15)) * 140, (0.08f * pow(1.5f*mountains[i], 4) + 0.3f) * 140, pow(mountains[i], 6) * 10);
        }
    }

    generateImage("output/map", width, length, island);
    std::cout << "Completed Map Generation";
}