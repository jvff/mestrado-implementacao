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

    PixelType getPixel(unsigned int x, unsigned int y) const {
        unused(x, y);

        return getDefaultPixelValue();
    }

    using Image<PixelType>::operator=;

protected:
    virtual PixelType getDefaultPixelValue() const = 0;
};

template <typename PixelType>
class FakeImage : public AbstractFakeImage<PixelType> {
public:
    using AbstractFakeImage<PixelType>::AbstractFakeImage;
    using AbstractFakeImage<PixelType>::operator=;

protected:
    PixelType getDefaultPixelValue() const {
        PixelType defaultValue;

        return defaultValue;
    }
};

template <>
class FakeImage<bool> : public AbstractFakeImage<bool> {
public:
    using AbstractFakeImage<bool>::AbstractFakeImage;
    using AbstractFakeImage<bool>::operator=;

protected:
    bool getDefaultPixelValue() const {
        return false;
    }
};

#endif
