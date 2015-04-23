#include <gtest/gtest.h>

#include "SimpleArrayImage.hpp"

#include "BoolImageTest.hpp"

typedef ::testing::Types<SimpleArrayImage<bool> > ImageTypes;
TYPED_TEST_CASE(BoolImageTest, ImageTypes);

TYPED_TEST(BoolImageTest, typeIsImage) {
    TypeParam* specificImage = NULL;
    Image<bool>* image = specificImage;
}

TYPED_TEST(BoolImageTest, typeIsntAbstract) {
    TypeParam* image = new TypeParam(1, 1);

    EXPECT_TRUE(image != NULL);

    delete image;
}

TYPED_TEST(BoolImageTest, twoDifferentPixels) {
    bool pixelValues[] = { true, false };

    this->testPixels(1, 2, pixelValues);
}

TYPED_TEST(BoolImageTest, verticalStripes) {
    int width = 8;
    int height = 4;
    bool pixelValues[width * height];
    bool* pixelIterator = &pixelValues[0];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x)
            *(pixelIterator++) = (x / 2) % 2 == 0;
    }

    this->testPixels(width, height, pixelValues);
}

TYPED_TEST(BoolImageTest, complexImage) {
    int width = 32;
    int height = 32;
    bool pixelValues[width * height];
    bool* pixelIterator = &pixelValues[0];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (x < width / 2 && y < height / 2)
                *pixelIterator = false;
            else if (x > width / 2 && y > height / 2)
                *pixelIterator = true;
            else if (x < width / 2)
                *pixelIterator = (x / 4) % 2 == 0;
            else
                *pixelIterator = (y / 4) % 2 == 0;

            ++pixelIterator;
        }
    }

    this->testPixels(width, height, pixelValues);
}
