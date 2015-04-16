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
