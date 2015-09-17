#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <algorithm>
#include <functional>

#include "Coordinate.hpp"
#include "Pixel.hpp"

template <typename ImagePixelType>
class Image {
public:
    using PixelType = ImagePixelType;

protected:
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;

    unsigned int width;
    unsigned int height;

public:
    Image(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
    }

    virtual ~Image() {
    }

    virtual Image& operator=(const Image<PixelType>& image) {
        auto smallestWidth = std::min(this->width, image.getWidth());
        auto smallestHeight = std::min(this->height, image.getHeight());

        for (unsigned int x = 0; x < smallestWidth; ++x) {
            for (unsigned int y = 0; y < smallestHeight; ++y)
                setPixel(x, y, image.getPixelValue(x, y));
        }

        return *this;
    }

    virtual Image& operator=(PaintFunction makePixel) {
        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x)
                setPixel(x, y, makePixel(x, y));
        }

        return *this;
    }

    virtual unsigned int getWidth() const {
        return width;
    }

    virtual unsigned int getHeight() const {
        return height;
    }

    void setPixel(const Coordinate& coordinate, const PixelType& value) {
        setPixel(coordinate.x, coordinate.y, value);
    }

    void setPixel(const Pixel<PixelType>& pixel) {
        setPixel(pixel.x, pixel.y, pixel.value);
    }

    Pixel<PixelType> getPixel(unsigned int x, unsigned int y) const {
        return Pixel<PixelType>(x, y, getPixelValue(x, y));
    }

    Pixel<PixelType> getPixel(const Coordinate& coordinate) const {
        return Pixel<PixelType>(coordinate, getPixelValue(coordinate));
    }

    PixelType getPixelValue(const Coordinate& coordinate) const {
        return getPixelValue(coordinate.x, coordinate.y);
    }

    virtual void setPixel(unsigned int x, unsigned int y, PixelType value) = 0;
    virtual PixelType getPixelValue(unsigned int x, unsigned int y) const = 0;
};

template <typename PixelType>
static bool allPixelsAreEqual(const Image<PixelType>& first,
        const Image<PixelType>& second) {
    unsigned int width = first.getWidth();
    unsigned int height = first.getHeight();

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            if (first.getPixelValue(x, y) != second.getPixelValue(x, y))
                return false;
        }
    }

    return true;
}

template <typename PixelType>
bool operator==(const Image<PixelType>& first, const Image<PixelType>& second) {
    return first.getWidth() == second.getWidth()
        && first.getHeight() == second.getHeight()
        && allPixelsAreEqual(first, second);
}

#endif
