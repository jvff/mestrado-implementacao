#ifndef MORPHOLOGICAL_RECONSTRUCTION_TESTS_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"

COMPLEX_FILTER_TEST_CASE(MorphologicalReconstructionTests);

COMPLEX_FILTER_TEST(markerSpreadsRight) {
    TestData<unsigned char>()
        .setDimensions(5, 3)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useLeftToRightHorizontalLine();
}

COMPLEX_FILTER_TEST(markerSpreadsDown) {
    TestData<unsigned char>()
        .setDimensions(3, 5)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useTopToBottomVerticalLine();
}

COMPLEX_FILTER_TEST(markerSpreadsRightAndDown) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(92)
        .setMarkerDepth(33)
        .useRectangleWithTopLeftMarker();
}

COMPLEX_FILTER_TEST(markerSpreadsLeft) {
    TestData<unsigned char>()
        .setDimensions(5, 3)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useRightToLeftHorizontalLine();
}

COMPLEX_FILTER_TEST(markerSpreadsUp) {
    TestData<unsigned char>()
        .setDimensions(3, 5)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useBottomToTopVerticalLine();
}

COMPLEX_FILTER_TEST(markerSpreadsLeftAndUp) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(250)
        .setMarkerDepth(99)
        .useRectangleWithBottomRightMarker();
}

COMPLEX_FILTER_TEST(markerSpreadsEverywhere) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(150)
        .setMarkerDepth(45)
        .useRectangleWithCenterMarker();
}

COMPLEX_FILTER_TEST(markerSpreadsToTopLeftCorner) {
    TestData<unsigned char>()
        .setDimensions(4, 4)
        .setBackground(0)
        .setForeground(111)
        .setMarkerDepth(101)
        .useRectangleOnTheTopLeftCornerWithBottomRightMarker();
}

COMPLEX_FILTER_TEST(markerSpreadsToAllCorners) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(98)
        .useFullImageWithCenterMarker();
}

COMPLEX_FILTER_TEST(middleIsntReconstructed) {
    TestData<unsigned char> test;

    test.setDimensions(7, 7)
        .setBackground(0)
        .setMarkerDepth(98);

    *test.sourceImage = [] (unsigned int x, unsigned int y) -> unsigned char {
        if (x == 0 || y == 0 || x == 6 || y == 6)
            return 0;
        else if (x == 1 || y == 1 || x == 5 || y == 5)
            return 240;
        else if (x == 2 || y == 2 || x ==  4|| y == 4)
            return 50;
        else
            return 192;
    };

    test.addMarker(1, 1);

    *test.expectedImage = [] (unsigned int x, unsigned int y) -> unsigned char {
        if (x == 0 || y == 0 || x == 6 || y == 6)
            return 0;
        else if (x == 1 || y == 1 || x == 5 || y == 5)
            return 98;
        else
            return 50;
    };
}

COMPLEX_FILTER_TEST(markerSpreadsThroughSpiral) {
    TestData<unsigned char> test;

    test.setDimensions(7, 7)
        .setBackground(0)
        .setMarkerDepth(255);

    *test.sourceImage = [] (unsigned int x, unsigned int y) -> unsigned char {
        if (x == 0 || y == 0 || x == 6 || y == 6)
            return 0;
        else if (x == 2 && y == 1)
            return 0;
        else if (x == 1 || y == 1 || x == 5 || y == 5)
            return 21;
        else if (x == 3 && y == 2)
            return 21;
        else if (x == 2 || y == 2 || x == 4 || y == 4)
            return 0;
        else
            return 21;
    };

    test.addMarker(1, 1);

    *test.expectedImage = *test.sourceImage;
}

REGISTER_COMPLEX_FILTER_TEST_CASE(MorphologicalReconstructionTests,
        markerSpreadsRight, markerSpreadsDown, markerSpreadsRightAndDown,
        markerSpreadsLeft, markerSpreadsUp, markerSpreadsLeftAndUp,
        markerSpreadsEverywhere, markerSpreadsToTopLeftCorner,
        markerSpreadsToAllCorners, middleIsntReconstructed,
        markerSpreadsThroughSpiral);

#endif
