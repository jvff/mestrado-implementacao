#include "WatershedFilterTest.hpp"

template <typename SourcePixelType,
        typename DestinationPixelType = SourcePixelType,
        typename DestinationImageType = SimpleArrayImage<DestinationPixelType>,
        typename SourceImageType = SimpleArrayImage<SourcePixelType> >
using TestData = WatershedFilterTestData<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType>;

TEST(WatershedFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = WatershedFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(WatershedFilterTest, defaultSourceImageTypeIsGenericImage) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using ImplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType>;
    using ExplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(WatershedFilterTest, isSubClassOfFilter) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using SubClass = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(WatershedFilterTest, isConstructible) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = WatershedFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isConstructible(WithoutParameters());
}

TEST(WatershedFilterTest, singleSegment) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .useSegmentGrid(1, 1)
        .setSeparatorWidth(0)
        .setSegmentDepths({10})
        .setSegmentOrder({1});
}

TEST(WatershedFilterTest, twoSegments) {
    TestData<unsigned char>()
        .setDimensions(3, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(1)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}

TEST(WatershedFilterTest, erosionFromTheRight) {
    TestData<unsigned char>()
        .setDimensions(5, 1)
        .useSegmentGrid(1, 5)
        .setSeparatorWidth(0)
        .setSegmentDepths({52, 101, 100, 100, 20})
        .setSegmentOrder({2, 2, 1, 1, 1});
}

TEST(WatershedFilterTest, twoSegmentsWithLargerSeparationBetweenThem) {
    TestData<unsigned char>()
        .setDimensions(4, 1)
        .useSegmentGrid(1, 2)
        .setSeparatorWidth(2)
        .setSeparatorDepth(100)
        .setSegmentDepths({20, 20})
        .setSegmentOrder({1, 2});
}
