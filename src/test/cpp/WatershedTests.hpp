#ifndef WATERSHED_TESTS_HPP
#define WATERSHED_TESTS_HPP

#include "ComplexFilterTestMacros.hpp"
#include "WatershedWaveImageTest.hpp"

COMPLEX_FILTER_TEST_CASE(WatershedTests);

COMPLEX_FILTER_TEST(singleSegment) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .useSegmentGrid(1, 1)
        .setSeparatorWidth(0)
        .setSegmentDepths({10})
        .setSegmentOrder({1});
}

COMPLEX_FILTER_TEST(twoSegments) {
    TestData<unsigned char>()
        .setDimensions(3, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(1)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}

COMPLEX_FILTER_TEST(erosionFromTheRight) {
    TestData<unsigned char>()
        .setDimensions(5, 1)
        .useSegmentGrid(1, 5)
        .setSeparatorWidth(0)
        .setSegmentDepths({52, 101, 100, 100, 20})
        .setSegmentOrder({2, 0, 1, 1, 1});
}

COMPLEX_FILTER_TEST(twoSegmentsWithLargerSeparationBetweenThem) {
    TestData<unsigned char>()
        .setDimensions(4, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(2)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}

COMPLEX_FILTER_TEST(twoVerticalSegments) {
    TestData<unsigned char>()
        .setDimensions(3, 9)
        .useSegmentGrid(2, 1)
        .setSeparatorWidth(4)
        .setSeparatorDepth(91)
        .setSegmentDepths({88, 84})
        .setSegmentOrder({2, 1});
}

COMPLEX_FILTER_TEST(twelveSegments) {
    TestData<unsigned char>()
        .setDimensions(110, 73)
        .useSegmentGrid(4, 3)
        .setSeparatorWidth(5)
        .setSeparatorDepth(100)
        .setSegmentDepths({31, 75, 42, 45, 9, 27, 99, 54, 74, 11, 22, 40})
        .setSegmentOrder({5, 11, 7, 8, 1, 4, 12, 9, 10, 2, 3, 6});
}

COMPLEX_FILTER_TEST(waveImage) {
    WatershedWaveImageTest<TestData<unsigned char> >();
}

REGISTER_COMPLEX_FILTER_TEST_CASE(WatershedTests, singleSegment, twoSegments,
        erosionFromTheRight, twoSegmentsWithLargerSeparationBetweenThem,
        twoVerticalSegments, twelveSegments, waveImage);

#endif
