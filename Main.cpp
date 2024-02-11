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

int main() {
    generateMap(1024, 1024);
    return 0;
}

void generateMap(int width, int length) 
{
    std::cout << "Generating map...\n";
    std::vector<float> height1 = NoiseGenerator::generatePerlinNoise(width, length, 512, 5);
    std::vector<float> height2 = NoiseGenerator::generatePerlinNoise(width, length, 512, 1);
    std::vector<float> height(width*length);
    for (int i = 0; i < height.size(); i++) height[i] = height1[i] * (0.17f * log2(9 * (height2[i]+0.018f)) + 0.45f);
    std::vector<Color> island(width*length);
    // Convert shades into grass, sand, or water
    for (int i = 0; i < height.size(); i++) {
        if(height[i] > 0.752f) {
            island[i] = Color(255, 255, 255);
        } else if(height[i] > 0.71f) {
            island[i] = Color(100, 100, 110);
        } else if (height[i] > 0.4f) {
            island[i] = Color(50, height[i]*255 + 50, 10);
        } else if (height[i] > 0.38f) {
            island[i] = Color(height[i]*255 + 70, height[i]*255 + 50, 0);
        } else {
            island[i] = Color(0, 120, 155);
        }
    }

    generateImage("output/map", width, length, island);
    std::cout << "Completed Map Generation";
}