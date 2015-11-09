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

REGISTER_COMPLEX_FILTER_TEST_CASE(AreaClosingTests, bigHoleIsntFilled,
        smallHoleIsFilled, twoSmallHolesAreFilled);

#endif
