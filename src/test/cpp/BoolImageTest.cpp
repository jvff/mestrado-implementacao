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
