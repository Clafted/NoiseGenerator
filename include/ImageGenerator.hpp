/**
 * The image generation structs and functions
 * (as commented below) are taken from a post on dev.to.
 * The link to the original code is here:
 * 
 * https://dev.to/muiz6/c-how-to-write-a-bitmap-image-from-scratch-1k6m
 * 
 * @author Noah Perez
 */
#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include "Color.hpp"

namespace ImageGenerator {
    // CODE FROM dev.to POST (LINK IS ABOVE ^^^)
    // ----------------------------------------------------------------------
    // Metadata, size of 40 bytes
    struct BmpInfoHeader {
        uint32_t sizeOfThisHeader = 40;
        int32_t width = 512; // in pixels
        int32_t height = 512; // in pixels
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
    };
    inline BmpInfoHeader bmpInfoHeader;

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
    };
    inline BmpHeader bmpHeader;

    struct Pixel {
        Color color;

        void save_on_file(std::ofstream& fout) {
            fout.write((char*)&color.b, sizeof(uint8_t));
            fout.write((char*)&color.g, sizeof(uint8_t));
            fout.write((char*)&color.r, sizeof(uint8_t));
        }
    };
    inline Pixel pixel;

    void generateImage(std::string fileName, int width, int height, std::vector<Color>& colors);
};
#endif