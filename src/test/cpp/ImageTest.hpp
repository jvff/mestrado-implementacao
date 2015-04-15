#ifndef IMAGE_TEST_H
#define IMAGE_TEST_H

#include <gtest/gtest.h>

#include "Image.hpp"

template <typename ImageType>
class ImageTest : public ::testing::Test {
protected:
    void testSinglePixel(int color);
    void testPixelsWithSameColor(int width, int height, int color);
    void testPixels(int width, int height, const int colors[]);
};

template <typename ImageType>
void ImageTest<ImageType>::testSinglePixel(int color) {
    testPixelsWithSameColor(1, 1, color);
}

template <typename ImageType>
void ImageTest<ImageType>::testPixelsWithSameColor(int width, int height,
        int color) {
    ImageType image(width, height);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            image.setPixel(x, y, color);
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            EXPECT_EQ(image.getPixel(x, y), color);
    }
}

template <typename ImageType>
void ImageTest<ImageType>::testPixels(int width, int height,
        const int colors[]) {
    ImageType image(width, height);
    const int* colorIterator = &colors[0];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            image.setPixel(x, y, *(colorIterator++));
    }

    colorIterator = &colors[0];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            EXPECT_EQ(image.getPixel(x, y), *(colorIterator++));
    }
}

#endif
