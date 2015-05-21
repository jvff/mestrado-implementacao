#ifndef FAKE_IMAGE_HPP
#define FAKE_IMAGE_HPP

#include "Image.hpp"

#include "Unused.hpp"

template <typename PixelType>
class AbstractFakeImage : public Image<PixelType> {
public:
    AbstractFakeImage(unsigned int width, unsigned int height)
            : Image<PixelType>(width, height) {
    }

    void setPixel(unsigned int x, unsigned int y, PixelType pixel) {
        unused(x, y, pixel);
    }

    PixelType getPixel(unsigned int x, unsigned int y) {
        unused(x, y);

        return getDefaultPixelValue();
    }

protected:
    virtual PixelType getDefaultPixelValue() = 0;
};

template <typename PixelType>
class FakeImage : public AbstractFakeImage<PixelType> {
public:
    using AbstractFakeImage<PixelType>::AbstractFakeImage;

protected:
    PixelType getDefaultPixelValue() {
        PixelType defaultValue;

        return defaultValue;
    }
};

template <>
class FakeImage<bool> : public AbstractFakeImage<bool> {
public:
    using AbstractFakeImage<bool>::AbstractFakeImage;

protected:
    bool getDefaultPixelValue() {
        return false;
    }
};

#endif
