#ifndef AREA_CLOSING_TESTS_HPP
#define AREA_CLOSING_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"

COMPLEX_FILTER_TEST_CASE(AreaClosingTests);

COMPLEX_FILTER_TEST(bigHoleIsntFilled) {
    TestData<unsigned char>()
        .setDimensions(6, 6)
        .setMaximumExtremitySize(9)
        .setBackground(199)
        .drawSquare(1, 1, 4, 100);
}

COMPLEX_FILTER_TEST(smallHoleIsFilled) {
    TestData<unsigned char>()
        .setDimensions(6, 6)
        .setMaximumExtremitySize(12)
        .setBackground(199)
        .drawSquare(1, 1, 2, 10);
}

COMPLEX_FILTER_TEST(twoSmallHolesAreFilled) {
    TestData<unsigned char>()
        .setDimensions(10, 9)
        .setMaximumExtremitySize(11)
        .setBackground(148)
        .drawSquare(1, 1, 2, 1)
        .drawSquare(4, 2, 3, 2);
}

COMPLEX_FILTER_TEST(valleyIsPartiallyFlattened) {
    TestData<unsigned char>()
        .setDimensions(15, 15)
        .setMaximumExtremitySize(50)
        .setBackground(30)
        .drawPyramid(1, 1, 13, 10, -1);
}

COMPLEX_FILTER_TEST(oneOfTwoHolesIsFilled) {
    TestData<unsigned char>()
        .setDimensions(10, 9)
        .setMaximumExtremitySize(6)
        .setBackground(252)
        .drawSquare(1, 1, 2, 101)
        .drawSquare(4, 2, 3, 102);
}

COMPLEX_FILTER_TEST(adjacentBigAndSmallHolesAreFilled) {
    TestData<unsigned char>()
        .setDimensions(8, 8)
        .setMaximumExtremitySize(65)
        .setBackground(51)
        .drawSquare(1, 1, 6, 40)
        .drawSquare(1, 6, 1, 45)
        .drawSquare(1, 5, 2, 50);
}

REGISTER_COMPLEX_FILTER_TEST_CASE(AreaClosingTests, bigHoleIsntFilled,
        smallHoleIsFilled, twoSmallHolesAreFilled, valleyIsPartiallyFlattened,
        oneOfTwoHolesIsFilled, adjacentBigAndSmallHolesAreFilled);

#endif
