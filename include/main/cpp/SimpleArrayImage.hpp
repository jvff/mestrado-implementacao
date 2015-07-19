#ifndef SIMPLE_ARRAY_IMAGE_HPP
#define SIMPLE_ARRAY_IMAGE_HPP

#include <vector>

#include "Image.hpp"

template <typename PixelType>
class SimpleArrayImage : public Image<PixelType> {
private:
    std::vector<PixelType> pixels;

    inline unsigned int getPixelIndex(unsigned int x, unsigned int y) const {
        return y * Image<PixelType>::width + x;
    }

public:
    SimpleArrayImage(unsigned int width, unsigned int height)
            : Image<PixelType>(width, height), pixels(width * height) {
    }

    using Image<PixelType>::operator=;

    void setPixel(unsigned int x, unsigned int y, PixelType value) {
        pixels[getPixelIndex(x, y)] = value;
    }

    PixelType getPixel(unsigned int x, unsigned int y) const {
        return pixels[getPixelIndex(x, y)];
    }
};

#endif
