#include "WatershedImplementationTest.hpp"

TEST(WatershedImplementationTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyImplementation = WatershedImplementation<DummyType, DummyType,
            ImageType>;

    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST(WatershedImplementationTest, defaultSourceImageTypeIsGenericImage) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using ImplicitType = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(WatershedImplementationTest, isConstructible) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using DummyImplementation = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(
            With<SourceImageParameter, DestinationImageParameter>());
}

TEST(WatershedImplementationTest, singleSegment) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .useSegmentGrid(1, 1)
        .setSeparatorWidth(0)
        .setSegmentDepths({10})
        .setSegmentOrder({1});
}

TEST(WatershedImplementationTest, twoSegments) {
    TestData<unsigned char>()
        .setDimensions(3, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(1)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}

TEST(WatershedImplementationTest, erosionFromTheRight) {
    TestData<unsigned char>()
        .setDimensions(5, 1)
        .useSegmentGrid(1, 5)
        .setSeparatorWidth(0)
        .setSegmentDepths({52, 101, 100, 100, 20})
        .setSegmentOrder({2, 2, 1, 1, 1});
}

TEST(WatershedImplementationTest, twoSegmentsWithLargerSeparationBetweenThem) {
    TestData<unsigned char>()
        .setDimensions(4, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(2)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}

TEST(WatershedImplementationTest, twoVerticalSegments) {
    TestData<unsigned char>()
        .setDimensions(3, 9)
        .useSegmentGrid(2, 1)
        .setSeparatorWidth(4)
        .setSeparatorDepth(91)
        .setSegmentDepths({88, 84})
        .setSegmentOrder({2, 1});
}

TEST(WatershedImplementationTest, twelveSegments) {
    TestData<unsigned char>()
        .setDimensions(110, 73)
        .useSegmentGrid(4, 3)
        .setSeparatorWidth(5)
        .setSeparatorDepth(100)
        .setSegmentDepths({31, 75, 42, 45, 9, 27, 99, 54, 74, 11, 22, 40})
        .setSegmentOrder({5, 11, 7, 8, 1, 4, 12, 9, 10, 2, 3, 6});
}
