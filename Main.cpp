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
#include "ImageGenerator.hpp"
#include "NoiseGenerator.hpp"
#include "Color.hpp"

using namespace ImageGenerator;

int main() {
    std::cout << "Generating noise...\n";
    std::vector<Color> colors = NoiseGenerator::generatePerlinNoise(512, 512, 128, 3);
    generateImage("output", 512, 512, colors);
    std::cout << "Completed Image Generation";
    return 0;
}

