#ifndef HMIN_TESTS_HPP
#define HMIN_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"

COMPLEX_FILTER_TEST_CASE(HminTests);

COMPLEX_FILTER_TEST(removesShallowHole) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setFeatureHeight(4)
        .setBackground(24)
        .drawSquare(1, 1, 5, 21)
        .setExpectedBackground(25);
}

COMPLEX_FILTER_TEST(doesntChangePeak) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setFeatureHeight(2)
        .setBackground(134)
        .drawSquare(1, 1, 5, 231)
        .setExpectedBackground(136)
        .drawExpectedSquare(1, 1, 5, 231);
}

COMPLEX_FILTER_TEST(shavesValleys) {
    TestData<unsigned char>()
        .setDimensions(6, 3)
        .setFeatureHeight(3)
        .setBackground(100)
        .setExpectedBackground(100)
        .drawSquare(1, 1, 1, 102)
        .drawExpectedSquare(1, 1, 1, 102)
        .drawSquare(3, 1, 1, 96)
        .drawExpectedSquare(3, 1, 1, 99)
        .drawSquare(5, 1, 1, 97)
        .drawSquare(1, 3, 1, 98)
        .drawSquare(3, 3, 1, 99)
        .drawSquare(5, 3, 1, 100);
}

REGISTER_COMPLEX_FILTER_TEST_CASE(HminTests, removesShallowHole,
        doesntChangePeak, shavesValleys);

#endif