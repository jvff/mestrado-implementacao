#ifndef WATERSHED_TESTS_HPP
#define WATERSHED_TESTS_HPP

#include <gtest/gtest.h>

template <typename TestData>
class WatershedTests : public testing::Test {
};

TYPED_TEST_CASE_P(WatershedTests);

TYPED_TEST_P(WatershedTests, singleSegment) {
    TypeParam()
        .setDimensions(5, 5)
        .useSegmentGrid(1, 1)
        .setSeparatorWidth(0)
        .setSegmentDepths({10})
        .setSegmentOrder({1});
}

TYPED_TEST_P(WatershedTests, twoSegments) {
    TypeParam()
        .setDimensions(3, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(1)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}

TYPED_TEST_P(WatershedTests, erosionFromTheRight) {
    TypeParam()
        .setDimensions(5, 1)
        .useSegmentGrid(1, 5)
        .setSeparatorWidth(0)
        .setSegmentDepths({52, 101, 100, 100, 20})
        .setSegmentOrder({2, 2, 1, 1, 1});
}

TYPED_TEST_P(WatershedTests, twoSegmentsWithLargerSeparationBetweenThem) {
    TypeParam()
        .setDimensions(4, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(2)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}

TYPED_TEST_P(WatershedTests, twoVerticalSegments) {
    TypeParam()
        .setDimensions(3, 9)
        .useSegmentGrid(2, 1)
        .setSeparatorWidth(4)
        .setSeparatorDepth(91)
        .setSegmentDepths({88, 84})
        .setSegmentOrder({2, 1});
}

TYPED_TEST_P(WatershedTests, twelveSegments) {
    TypeParam()
        .setDimensions(110, 73)
        .useSegmentGrid(4, 3)
        .setSeparatorWidth(5)
        .setSeparatorDepth(100)
        .setSegmentDepths({31, 75, 42, 45, 9, 27, 99, 54, 74, 11, 22, 40})
        .setSegmentOrder({5, 11, 7, 8, 1, 4, 12, 9, 10, 2, 3, 6});
}

REGISTER_TYPED_TEST_CASE_P(WatershedTests, singleSegment, twoSegments,
        erosionFromTheRight, twoSegmentsWithLargerSeparationBetweenThem,
        twoVerticalSegments, twelveSegments);

#endif
