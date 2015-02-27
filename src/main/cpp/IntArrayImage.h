#ifndef INT_ARRAY_IMAGE_H
#define INT_ARRAY_IMAGE_H

#include "Image.h"

class IntArrayImage : public Image {
private:
    int* pixels;

    inline int getPixelIndex(int x, int y) {
        return y * width + x;
    }

public:
    IntArrayImage(int width, int height) : Image(width, height) {
        pixels = new int[width * height];
    }

    void setPixel(int x, int y, int color) {
        pixels[getPixelIndex(x, y)] = color;
    }

    int getPixel(int x, int y) {
        return pixels[getPixelIndex(x, y)];
    }
};

#endif
