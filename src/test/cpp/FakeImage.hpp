#ifndef FAKE_IMAGE_HPP
#define FAKE_IMAGE_HPP

#include "Image.hpp"

template <typename PixelType>
class FakeImage : public Image<PixelType> {
public:
    FakeImage(int width, int height) : Image<PixelType>(width, height) {
    }

    void setPixel(int x, int y, PixelType pixel) {
    }

    PixelType getPixel(int x, int y) {
        return PixelType{};
    }
};

#endif