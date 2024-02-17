#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include "Color.hpp"
#include <vector>

namespace NoiseGenerator {
    std::vector<float> generatePerlinNoise(int width, int height, int spacing, int intervals);
    std::vector<float> generateWorleyNoise(int width, int height, int spacing);
};

#endif