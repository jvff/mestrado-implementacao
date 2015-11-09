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

REGISTER_COMPLEX_FILTER_TEST_CASE(AreaClosingTests, bigHoleIsntFilled);

#endif
