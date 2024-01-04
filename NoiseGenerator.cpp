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

// CODE FROM dev.to POST (LINK IS ABOVE ^^^)
// ----------------------------------------------------------------------
// Metadata size of 14 bytes (look at variable types)
struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54 + 786432;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;

    void save_on_file(std::ofstream& fout) {
        fout.write(this->bitmapSignatureBytes, 2);
        fout.write((char*)&this->sizeOfBitmapFile, sizeof(uint32_t));
        fout.write((char*)&this->reservedBytes, sizeof(uint32_t));
        fout.write((char*)&this->pixelDataOffset, sizeof(uint32_t));
    }
} bmpHeader;

// Also metadata, size of 40 bytes
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
} bmpInfoHeader;

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


int main() {

    // Image generation code (also from dev.to post)
    // ----------------------------------------------------------------------
    std::ofstream fout("../../output4.bmp", std::ios::binary);
    
    bmpHeader.save_on_file(fout);
    bmpInfoHeader.save_on_file(fout);
    size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
    for (int i = 0; i < numberOfPixels; i++) {
        pixel.r = 255 * ((std::cos(3.14 * ((float) (i % bmpInfoHeader.width) / bmpInfoHeader.width)) + 1) / 2);
        pixel.g = 255 * ((std::cos(3.14 * ((float) (i / bmpInfoHeader.height) / bmpInfoHeader.height)) + 1) / 2);
        pixel.b = 255 * ((-std::cos(3.14 * ((float) (i % bmpInfoHeader.width) / bmpInfoHeader.width)) + 1) / 2);
        pixel.save_on_file(fout);
    }
    fout.close();
    // ----------------------------------------------------------------------
    
    std::cout << "Completed Image Generation";
    return 0;
}