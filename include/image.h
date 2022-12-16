#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <iostream>
// #include <cstdio>
#include <math.h>

enum ImageType{
    PNG, JPG, BMP, TGA
};

struct Image{
    uint8_t *data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;

    Image(const char* filename);
    Image(int w, int h, int channels);
    Image(const Image &img);
    ~Image();
    bool read(const char* filename);
    bool write(const char* filename);
    ImageType getFileType(const char* filename);

    Image& grayscale_avg();
    Image& grayscale_lum();
    Image& colorMask(float r, float g, float b);
    Image& crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch);

    Image& diffmap(Image &img);
    Image& diffmap_scale(Image& img, uint8_t scl = 0);

    Image& flipX();
    Image& flipY();
};

#endif