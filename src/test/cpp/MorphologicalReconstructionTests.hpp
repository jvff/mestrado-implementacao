#ifndef MORPHOLOGICAL_RECONSTRUCTION_TESTS_HPP
#define MORPHOLOGICAL_RECONSTRUCTION_TESTS_HPP

#include <gtest/gtest.h>

template <typename TestData>
class MorphologicalReconstructionTests : public testing::Test {
};

TYPED_TEST_CASE_P(MorphologicalReconstructionTests);

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsRight) {
    TypeParam()
        .setDimensions(5, 3)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useLeftToRightHorizontalLine();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsDown) {
    TypeParam()
        .setDimensions(3, 5)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useTopToBottomVerticalLine();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsRightAndDown) {
    TypeParam()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(92)
        .setMarkerDepth(33)
        .useRectangleWithTopLeftMarker();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsLeft) {
    TypeParam()
        .setDimensions(5, 3)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useRightToLeftHorizontalLine();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsUp) {
    TypeParam()
        .setDimensions(3, 5)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useBottomToTopVerticalLine();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsLeftAndUp) {
    TypeParam()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(250)
        .setMarkerDepth(99)
        .useRectangleWithBottomRightMarker();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsEverywhere) {
    TypeParam()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(150)
        .setMarkerDepth(45)
        .useRectangleWithCenterMarker();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsToTopLeftCorner) {
    TypeParam()
        .setDimensions(4, 4)
        .setBackground(0)
        .setForeground(111)
        .setMarkerDepth(101)
        .useRectangleOnTheTopLeftCornerWithBottomRightMarker();
}

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsToAllCorners) {
    TypeParam()
        .setDimensions(7, 7)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(98)
        .useFullImageWithCenterMarker();
}

TYPED_TEST_P(MorphologicalReconstructionTests, middleIsntReconstructed) {
    TypeParam test;

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

TYPED_TEST_P(MorphologicalReconstructionTests, markerSpreadsThroughSpiral) {
    TypeParam test;

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

REGISTER_TYPED_TEST_CASE_P(MorphologicalReconstructionTests, markerSpreadsRight,
        markerSpreadsDown, markerSpreadsRightAndDown, markerSpreadsLeft,
        markerSpreadsUp, markerSpreadsLeftAndUp, markerSpreadsEverywhere,
        markerSpreadsToTopLeftCorner, markerSpreadsToAllCorners,
        middleIsntReconstructed, markerSpreadsThroughSpiral);

#endif
