#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "Image.hpp"

template <typename ImageType, typename PixelType>
class ImageTest : public ::testing::Test {
protected:
    void testSinglePixel(PixelType value);
    void testPixelsWithSameValue(int width, int height, PixelType values);
    void testPixels(int width, int height, const PixelType values[]);
    virtual void comparePixel(PixelType a, PixelType b) = 0;
};

template <typename ImageType, typename PixelType>
void ImageTest<ImageType, PixelType>::testSinglePixel(PixelType value) {
    testPixelsWithSameValue(1, 1, value);
}

template <typename ImageType, typename PixelType>
void ImageTest<ImageType, PixelType>::testPixelsWithSameValue(int width,
        int height, PixelType value) {
    ImageType image(width, height);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            image.setPixel(x, y, value);
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            comparePixel(image.getPixel(x, y), value);
    }
}

template <typename ImageType, typename PixelType>
void ImageTest<ImageType, PixelType>::testPixels(int width, int height,
        const PixelType values[]) {
    ImageType image(width, height);
    const PixelType* pixelIterator = &values[0];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            image.setPixel(x, y, *(pixelIterator++));
    }

    pixelIterator = &values[0];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            comparePixel(image.getPixel(x, y), *(pixelIterator++));
    }
}

#endif