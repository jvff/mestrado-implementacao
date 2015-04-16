#ifndef SIMPLE_ARRAY_IMAGE_HPP
#define SIMPLE_ARRAY_IMAGE_HPP

#include "Image.hpp"

template <typename PixelType>
class SimpleArrayImage : public Image<int> {
private:
    int* pixels;

    inline int getPixelIndex(int x, int y) {
        return y * width + x;
    }

public:
    SimpleArrayImage(int width, int height) : Image(width, height) {
        pixels = new int[width * height];
    }

    ~SimpleArrayImage() {
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
