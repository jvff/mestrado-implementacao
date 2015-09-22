#ifndef AREA_OPENING_TESTS_HPP
#define AREA_OPENING_TESTS_HPP

#include <gtest/gtest.h>

template <typename TestData>
class AreaOpeningTests : public testing::Test {
};

TYPED_TEST_CASE_P(AreaOpeningTests);

TYPED_TEST_P(AreaOpeningTests, bigPlateauIsntCleared) {
    TypeParam()
        .setDimensions(6, 6)
        .setMaximumPeakSize(9)
        .setBackground(102)
        .drawSquare(1, 1, 4, 167);
}

TYPED_TEST_P(AreaOpeningTests, smallPlateauIsCleared) {
    TypeParam()
        .setDimensions(6, 6)
        .setMaximumPeakSize(12)
        .setBackground(13)
        .drawSquare(1, 1, 2, 201);
}

TYPED_TEST_P(AreaOpeningTests, twoSmallPlateausAreCleared) {
    TypeParam()
        .setDimensions(10, 9)
        .setMaximumPeakSize(11)
        .setBackground(148)
        .drawSquare(1, 1, 2, 252)
        .drawSquare(4, 2, 3, 251);
}

TYPED_TEST_P(AreaOpeningTests, peakIsPartiallyFlattened) {
    TypeParam()
        .setDimensions(15, 15)
        .setMaximumPeakSize(50)
        .setBackground(3)
        .drawPyramid(1, 1, 13, 10);
}

TYPED_TEST_P(AreaOpeningTests, oneOfTwoPlateausIsCleared) {
    TypeParam()
        .setDimensions(10, 9)
        .setMaximumPeakSize(6)
        .setBackground(148)
        .drawSquare(1, 1, 2, 252)
        .drawSquare(4, 2, 3, 251);
}

TYPED_TEST_P(AreaOpeningTests, adjacentBigAndSmallPlateausAreCleared) {
    TypeParam()
        .setDimensions(8, 8)
        .setMaximumPeakSize(65)
        .setBackground(30)
        .drawSquare(1, 1, 6, 50)
        .drawSquare(1, 6, 1, 45)
        .drawSquare(1, 5, 2, 40);
}

REGISTER_TYPED_TEST_CASE_P(AreaOpeningTests, bigPlateauIsntCleared,
        smallPlateauIsCleared, twoSmallPlateausAreCleared,
        peakIsPartiallyFlattened, oneOfTwoPlateausIsCleared,
        adjacentBigAndSmallPlateausAreCleared);

#endif
