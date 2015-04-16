#ifndef INT_ARRAY_IMAGE_HPP
#define INT_ARRAY_IMAGE_HPP

#include "Image.hpp"

class IntArrayImage : public Image<int> {
private:
    int* pixels;

    inline int getPixelIndex(int x, int y) {
        return y * width + x;
    }

public:
    IntArrayImage(int width, int height) : Image(width, height) {
        pixels = new int[width * height];
    }

    ~IntArrayImage() {
        delete[] pixels;
    }

    void setPixel(int x, int y, int color) {
        pixels[getPixelIndex(x, y)] = color;
    }

    int getPixel(int x, int y) {
        return pixels[getPixelIndex(x, y)];
    }
};

#endif
