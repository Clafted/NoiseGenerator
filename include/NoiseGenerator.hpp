#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include "Color.hpp"
#include <vector>

namespace NoiseGenerator {
    std::vector<Color> generatePerlinNoise(int width, int height, int spacing, int intervals);
};

#endif