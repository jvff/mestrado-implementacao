#include "BoolImageTest.hpp"

using ImageTypes = ::testing::Types<SimpleArrayImage<bool> >;
TYPED_TEST_CASE(BoolImageTest, ImageTypes);

TYPED_TEST(BoolImageTest, typeIsImage) {
    AssertThat<TypeParam>::isSubClass(Of<Image<bool> >());
}

TYPED_TEST(BoolImageTest, typeIsntAbstract) {
    AssertThat<TypeParam>::isConstructible(With<unsigned int, unsigned int>());
}

TYPED_TEST(BoolImageTest, twoDifferentPixels) {
    bool pixelValues[] = { true, false };

    this->testPixels(1, 2, pixelValues);
}

TYPED_TEST(BoolImageTest, verticalStripes) {
    const unsigned int width = 8;
    const unsigned int height = 4;
    bool pixelValues[width * height];
    bool* pixelIterator = &pixelValues[0];

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x)
            *(pixelIterator++) = (x / 2) % 2 == 0;
    }

    this->testPixels(width, height, pixelValues);
}

TYPED_TEST(BoolImageTest, complexImage) {
    const unsigned int width = 32;
    const unsigned int height = 32;
    bool pixelValues[width * height];
    bool* pixelIterator = &pixelValues[0];

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
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
