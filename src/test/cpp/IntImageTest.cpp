#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"

#include "IntImageTest.hpp"

using ImageTypes = ::testing::Types<SimpleArrayImage<int> >;
TYPED_TEST_CASE(IntImageTest, ImageTypes);

TYPED_TEST(IntImageTest, typeIsImage) {
    AssertThat<TypeParam>::isSubClass(Of<Image<int> >());
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
    const unsigned int width = 9;
    const unsigned int height = 5;
    int values[width * height];
    int *valueIterator = &values[0];

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
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
