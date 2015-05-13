#include <gtest/gtest.h>

#include "SimpleArrayImage.hpp"

#include "IntImageTest.hpp"

typedef ::testing::Types<SimpleArrayImage<int> > ImageTypes;
TYPED_TEST_CASE(IntImageTest, ImageTypes);

TYPED_TEST(IntImageTest, typeIsImage) {
    EXPECT_TRUE((std::is_base_of<Image<int>, TypeParam>::value));
}

TYPED_TEST(IntImageTest, testSinglePixel) {
    this->testSinglePixel(10);
}

TYPED_TEST(IntImageTest, testSinglePixelMaxValue) {
    this->testSinglePixel(0xFFFFFFFF);
}

TYPED_TEST(IntImageTest, testTwoPixelsWithTheSameValue) {
    this->testPixelsWithSameValue(2, 1, 10);
}

TYPED_TEST(IntImageTest, testTwoPixelsWithDifferentValues) {
    int values[] = { 10, 20 };

    this->testPixels(2, 1, values);
}

TYPED_TEST(IntImageTest, testRedGreenBlueRect) {
    int width = 9;
    int height = 5;
    int values[width * height];
    int *valueIterator = &values[0];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            switch (y % 5) {
                case 0:
                case 1:
                case 2:
                    *valueIterator++ = 0xFF << (2 * (x % 3));
                    break;
                case 3:
                    *valueIterator++ = 0x00000000;
                    break;
                case 4:
                    *valueIterator++ = 0xFFFFFFFF;
                    break;
            };
        }
    }

    this->testPixels(width, height, values);
}
