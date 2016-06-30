#include "MorphologicalGradientFilterImplementationTests.hpp"

using ImageTypes = ::testing::Types<
        TestAliases<Image, SimpleArrayImage> >;

TYPED_TEST_CASE(MorphologicalGradientFilterImplementationTests, ImageTypes);

TEST_C(binarySquare) {
    TestData<bool>()
        .setDimensions(10, 10)
        .setStructureSize(1)
        .setBackground(false)
        .drawSquare(2, 2, 6, true);
}

TEST_C(grayscaleSquare) {
    TestData<unsigned char>()
        .setDimensions(10, 10)
        .setStructureSize(2)
        .setBackground(20)
        .drawSquare(2, 2, 6, 27);
}

TEST_C(twoGrayscaleSquares) {
    TestData<unsigned char>()
        .setDimensions(23, 15)
        .setStructureSize(3)
        .setBackground(100)
        .drawSquare(4, 4, 7, 101)
        .drawSquare(12, 4, 7, 102);
}

TEST_C(threeGrayscaleSquares) {
    TestData<unsigned char>()
        .setDimensions(23, 15)
        .setStructureSize(1)
        .setBackground(100)
        .drawSquare(4, 4, 7, 101)
        .drawSquare(12, 4, 7, 102)
        .drawSquare(10, 6, 3, 109);
}
