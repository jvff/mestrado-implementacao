#include <gtest/gtest.h>

#include "IntArrayImage.hpp"

#include "IntImageTest.hpp"

typedef ::testing::Types<IntArrayImage> ImageTypes;
TYPED_TEST_CASE(IntImageTest, ImageTypes);

TYPED_TEST(IntImageTest, typeIsImage) {
    TypeParam* specificImage = NULL;
    Image<int>* image = specificImage;
}

TYPED_TEST(IntImageTest, typeIsRgbImage) {
    TypeParam* specificImage = NULL;
    RgbImage* rgbImage = specificImage;
}

TYPED_TEST(IntImageTest, testSinglePixel) {
    this->testSinglePixel(10);
}

TYPED_TEST(IntImageTest, testSingleRedPixel) {
    this->testSinglePixel(0xFF0000);
}

TYPED_TEST(IntImageTest, testTwoPixelsWithTheSameValue) {
    this->testPixelsWithSameValue(2, 1, 10);
}

TYPED_TEST(IntImageTest, testTwoPixelsWithDifferentColors) {
    int colors[] = { 10, 20 };

    this->testPixels(2, 1, colors);
}

TYPED_TEST(IntImageTest, testRedGreenBlueRect) {
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
