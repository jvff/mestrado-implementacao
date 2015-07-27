#include "MorphologicalReconstructionFilterTest.hpp"

TEST(MorphologicalReconstructionFilterTest, classIsntAbstract) {
    using PixelType = DummyType;
    using ImageType = FakeImage<PixelType>;
    using FilterClass = MorphologicalReconstructionFilter<PixelType, ImageType>;

    AssertThat<FilterClass>::isConstructible(WithoutParameters());
}

TEST(MorphologicalReconstructionFilterTest, isFilter) {
    using PixelType = DummyType;
    using ImageType = FakeImage<PixelType>;
    using FilterClass = MorphologicalReconstructionFilter<PixelType, ImageType>;
    using ParentFilterClass = Filter<PixelType, PixelType, ImageType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}

TEST(MorphologicalReconstructionFilterTest, defaultSourceImageType) {
    using PixelType = DummyType;
    using DestinationImageType = FakeImage<PixelType>;
    using SourceImageType = Image<PixelType>;
    using ImplicitType = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType>;
    using ExplicitType = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(MorphologicalReconstructionFilterTest, sourceImageTypeIsPropagated) {
    using PixelType = DummyType;
    using DestinationImageType = FakeImage<PixelType>;
    using SourceImageType = FakeImage<PixelType>;
    using FilterClass = MorphologicalReconstructionFilter<PixelType,
            DestinationImageType, SourceImageType>;
    using ParentFilterClass = Filter<PixelType, PixelType, DestinationImageType,
            SourceImageType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsRight) {
    TestData<unsigned char>()
        .setDimensions(5, 3)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useLeftToRightHorizontalLine();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsDown) {
    TestData<unsigned char>()
        .setDimensions(3, 5)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useTopToBottomVerticalLine();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsRightAndDown) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(92)
        .setMarkerDepth(33)
        .useRectangleWithTopLeftMarker();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsLeft) {
    TestData<unsigned char>()
        .setDimensions(5, 3)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useRightToLeftHorizontalLine();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsUp) {
    TestData<unsigned char>()
        .setDimensions(3, 5)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(10)
        .useBottomToTopVerticalLine();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsLeftAndUp) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(250)
        .setMarkerDepth(99)
        .useRectangleWithBottomRightMarker();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsEverywhere) {
    TestData<unsigned char>()
        .setDimensions(5, 5)
        .setBackground(0)
        .setForeground(150)
        .setMarkerDepth(45)
        .useRectangleWithCenterMarker();
}
