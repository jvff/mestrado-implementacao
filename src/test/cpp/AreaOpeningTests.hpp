#ifndef AREA_OPENING_TESTS_HPP
#define AREA_OPENING_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"

COMPLEX_FILTER_TEST_CASE(AreaOpeningTests);

COMPLEX_FILTER_TEST(bigPlateauIsntCleared) {
    TestData<unsigned char>()
        .setDimensions(6, 6)
        .setMaximumPeakSize(9)
        .setBackground(102)
        .drawSquare(1, 1, 4, 167);
}

COMPLEX_FILTER_TEST(smallPlateauIsCleared) {
    TestData<unsigned char>()
        .setDimensions(6, 6)
        .setMaximumPeakSize(12)
        .setBackground(13)
        .drawSquare(1, 1, 2, 201);
}

COMPLEX_FILTER_TEST(twoSmallPlateausAreCleared) {
    TestData<unsigned char>()
        .setDimensions(10, 9)
        .setMaximumPeakSize(11)
        .setBackground(148)
        .drawSquare(1, 1, 2, 252)
        .drawSquare(4, 2, 3, 251);
}

COMPLEX_FILTER_TEST(peakIsPartiallyFlattened) {
    TestData<unsigned char>()
        .setDimensions(15, 15)
        .setMaximumPeakSize(50)
        .setBackground(3)
        .drawPyramid(1, 1, 13, 10);
}

COMPLEX_FILTER_TEST(oneOfTwoPlateausIsCleared) {
    TestData<unsigned char>()
        .setDimensions(10, 9)
        .setMaximumPeakSize(6)
        .setBackground(148)
        .drawSquare(1, 1, 2, 252)
        .drawSquare(4, 2, 3, 251);
}

COMPLEX_FILTER_TEST(adjacentBigAndSmallPlateausAreCleared) {
    TestData<unsigned char>()
        .setDimensions(8, 8)
        .setMaximumPeakSize(65)
        .setBackground(30)
        .drawSquare(1, 1, 6, 50)
        .drawSquare(1, 6, 1, 45)
        .drawSquare(1, 5, 2, 40);
}

REGISTER_COMPLEX_FILTER_TEST_CASE(AreaOpeningTests, bigPlateauIsntCleared,
        smallPlateauIsCleared, twoSmallPlateausAreCleared,
        peakIsPartiallyFlattened, oneOfTwoPlateausIsCleared,
        adjacentBigAndSmallPlateausAreCleared);

#endif
