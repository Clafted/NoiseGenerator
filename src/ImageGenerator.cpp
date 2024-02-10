#include "../include/ImageGenerator.hpp"
#include <vector>

void ImageGenerator::generateImage(std::string fileName, int width, int height, std::vector<Color>& colors) {
    bmpInfoHeader.width = width;
    bmpInfoHeader.height = height;
    // Image generation code (using code from dev.to post)
    // ----------------------------------------------------------------------
    std::ofstream fout(fileName + ".bmp", std::ios::binary);
    bmpHeader.save_on_file(fout);
    bmpInfoHeader.save_on_file(fout);
    for (int i = 0; i < colors.size(); i++) {
        pixel.color = colors[colors.size() - 1 - i];
        pixel.save_on_file(fout);
    }
    fout.close();
}