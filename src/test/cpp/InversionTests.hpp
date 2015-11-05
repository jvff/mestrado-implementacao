#ifndef INVERSION_TESTS_HPP
#define INVERSION_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"

COMPLEX_FILTER_TEST_CASE(InversionTests);

COMPLEX_FILTER_TEST(uniformImageIsntChanged) {
    typename TestFixture::template TestData<unsigned char>()
        .setDimensions(2, 2)
        .setPixel(0, 0, 100)
        .setPixel(0, 1, 100)
        .setPixel(1, 0, 100)
        .setPixel(1, 1, 100);
}

COMPLEX_FILTER_TEST(pixelsAreSwapped) {
    typename TestFixture::template TestData<unsigned char>()
        .setDimensions(2, 2)
        .setPixel(0, 0, 12)
        .setPixel(0, 1, 200)
        .setPixel(1, 0, 200)
        .setPixel(1, 1, 12);
}

COMPLEX_FILTER_TEST(pixelsAreSwappedAndMiddleValueIsKept) {
    typename TestFixture::template TestData<unsigned char>()
        .setDimensions(2, 2)
        .setPixel(0, 0, 12)
        .setPixel(0, 1, 106)
        .setPixel(1, 0, 106)
        .setPixel(1, 1, 200);
}

COMPLEX_FILTER_TEST(imageWithDifferentPixels) {
    typename TestFixture::template TestData<unsigned char>()
        .setDimensions(3, 2)
        .setPixel(0, 0, 92)
        .setPixel(0, 1, 100)
        .setPixel(1, 0, 145)
        .setPixel(1, 1, 140)
        .setPixel(2, 0, 155)
        .setPixel(2, 1, 200);
}

COMPLEX_FILTER_TEST(uniformImageIsDisplacedByCustomRange) {
    typename TestFixture::template TestData<unsigned char>()
        .setDimensions(2, 2)
        .setRange(36, 140)
        .setPixel(0, 0, 37)
        .setPixel(0, 1, 37)
        .setPixel(1, 0, 37)
        .setPixel(1, 1, 37);
}

COMPLEX_FILTER_TEST(imageWithDifferentPixelsAndCustomRange) {
    typename TestFixture::template TestData<unsigned char>()
        .setDimensions(2, 3)
        .setRange(22, 250)
        .setPixel(0, 0, 40)
        .setPixel(0, 1, 34)
        .setPixel(0, 2, 249)
        .setPixel(1, 0, 89)
        .setPixel(1, 1, 200)
        .setPixel(1, 2, 111);
}

COMPLEX_FILTER_TEST(floatingPointImage) {
    typename TestFixture::template TestData<float>()
        .setDimensions(3, 2)
        .setPixel(0, 0, 0.008f)
        .setPixel(0, 1, 12.75f)
        .setPixel(1, 0, -100.2f)
        .setPixel(1, 1, 1.1e4f)
        .setPixel(2, 0, 1.1e7f)
        .setPixel(2, 1, 9.2e7f);
}

COMPLEX_FILTER_TEST(floatingPointImageWithCustomRange) {
    typename TestFixture::template TestData<float>()
        .setDimensions(2, 3)
        .setRange(-1.3e7f, 9.3e7f)
        .setPixel(0, 0, 0.008f)
        .setPixel(0, 1, 12.75f)
        .setPixel(0, 2, -100.2f)
        .setPixel(1, 0, 1.1e4f)
        .setPixel(1, 1, 1.1e7f)
        .setPixel(1, 2, 9.2e7f);
}

REGISTER_COMPLEX_FILTER_TEST_CASE(InversionTests, uniformImageIsntChanged,
        pixelsAreSwapped, pixelsAreSwappedAndMiddleValueIsKept,
        imageWithDifferentPixels, uniformImageIsDisplacedByCustomRange,
        imageWithDifferentPixelsAndCustomRange, floatingPointImage,
        floatingPointImageWithCustomRange);

#endif
