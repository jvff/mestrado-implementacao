#ifndef SIMPLE_ARRAY_IMAGE_HPP
#define SIMPLE_ARRAY_IMAGE_HPP

#include "Image.hpp"

template <typename PixelType>
class SimpleArrayImage : public Image<PixelType> {
private:
    PixelType* pixels;

    inline int getPixelIndex(int x, int y) {
        return y * Image<PixelType>::width + x;
    }

public:
    SimpleArrayImage(int width, int height) : Image<PixelType>(width, height) {
        pixels = new PixelType[width * height];
    }

    ~SimpleArrayImage() {
        delete[] pixels;
    }

    void setPixel(int x, int y, PixelType value) {
        pixels[getPixelIndex(x, y)] = value;
    }

    PixelType getPixel(int x, int y) {
        return pixels[getPixelIndex(x, y)];
    }
};

#endif
