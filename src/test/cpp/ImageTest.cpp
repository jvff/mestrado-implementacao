#include <gtest/gtest.h>

#include "IntArrayImage.hpp"

#include "ImageTest.hpp"

typedef ::testing::Types<IntArrayImage> ImageTypes;
TYPED_TEST_CASE(ImageTest, ImageTypes);

TYPED_TEST(ImageTest, testSinglePixel) {
    this->testSinglePixel(10);
}

TYPED_TEST(ImageTest, testSingleRedPixel) {
    this->testSinglePixel(0xFF0000);
}

TYPED_TEST(ImageTest, testTwoPixelsWithTheSameColor) {
    this->testPixelsWithSameColor(2, 1, 10);
}

TYPED_TEST(ImageTest, testTwoPixelsWithDifferentColors) {
    int colors[] = { 10, 20 };

    this->testPixels(2, 1, colors);
}

TYPED_TEST(ImageTest, testRedGreenBlueRect) {
    int width = 9;
    int height = 5;
    int colors[width * height];
    int *colorIterator = &colors[0];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            switch (y % 5) {
                case 0:
                case 1:
                case 2:
                    *colorIterator++ = 0xFF << (2 * (x % 3));
                    break;
                case 3:
                    *colorIterator++ = 0x00000000;
                    break;
                case 4:
                    *colorIterator++ = 0xFFFFFFFF;
                    break;
            };
        }
    }

    this->testPixels(width, height, colors);
}

template <typename ImageType>
void ImageTest<ImageType>::testSinglePixel(int color) {
    testPixelsWithSameColor(1, 1, color);
}

template <typename ImageType>
void ImageTest<ImageType>::testPixelsWithSameColor(int width, int height, int color) {
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
void ImageTest<ImageType>::testPixels(int width, int height, const int colors[]) {
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
