#ifndef FAKE_IMAGE_HPP
#define FAKE_IMAGE_HPP

#include "Image.hpp"

#include "Unused.hpp"

template <typename PixelType>
class FakeImage : public Image<PixelType> {
public:
    FakeImage(unsigned int width, unsigned int height)
            : Image<PixelType>(width, height) {
    }

    void setPixel(unsigned int x, unsigned int y, PixelType pixel) {
        unused(x, y, pixel);
    }

    PixelType getPixel(unsigned int x, unsigned int y) {
        unused(x, y);

        PixelType defaultValue;

        return defaultValue;
    }
};

#endif
