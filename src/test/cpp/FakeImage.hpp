#ifndef FAKE_IMAGE_HPP
#define FAKE_IMAGE_HPP

#include "Image.hpp"

#include "Unused.hpp"

template <typename PixelType>
class FakeImage : public Image<PixelType> {
public:
    FakeImage(int width, int height) : Image<PixelType>(width, height) {
    }

    void setPixel(int x, int y, PixelType pixel) {
        unused(x, y, pixel);
    }

    PixelType getPixel(int x, int y) {
        unused(x, y);

        PixelType defaultValue;

        return defaultValue;
    }
};

#endif
