#include <gtest/gtest.h>

#include "ImageTest.h"


TEST_F(ImageTest, testSinglePixel) {
    testSinglePixel(10);
}

TEST_F(ImageTest, testSingleRedPixel) {
    testSinglePixel(0xFF0000);
}

TEST_F(ImageTest, testTwoPixelsWithTheSameColor) {
    testPixelsWithSameColor(2, 1, 10);
}

TEST_F(ImageTest, testTwoPixelsWithDifferentColors) {
    int colors[] = { 10, 20 };

    testPixels(2, 1, colors);
}

TEST_F(ImageTest, testRedGreenBlueRect) {
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

    testPixels(width, height, colors);
}

void ImageTest::testSinglePixel(int color) {
    testPixelsWithSameColor(1, 1, color);
}

void ImageTest::testPixelsWithSameColor(int width, int height, int color) {
    Image image(width, height);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            image.setPixel(x, y, color);
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y)
            EXPECT_EQ(image.getPixel(x, y), color);
    }
}

void ImageTest::testPixels(int width, int height, const int colors[]) {
    Image image(width, height);
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
