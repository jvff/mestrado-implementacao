#include "MorphologicalReconstructionFilterTest.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = MorphologicalReconstructionFilterTestData<PixelType,
        ImageType>;

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

TEST(MorphologicalReconstructionFilterTest, markerSpreadsToTopLeftCorner) {
    TestData<unsigned char>()
        .setDimensions(4, 4)
        .setBackground(0)
        .setForeground(111)
        .setMarkerDepth(101)
        .useRectangleOnTheTopLeftCornerWithBottomRightMarker();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsToAllCorners) {
    TestData<unsigned char>()
        .setDimensions(7, 7)
        .setBackground(0)
        .setForeground(100)
        .setMarkerDepth(98)
        .useFullImageWithCenterMarker();
}

TEST(MorphologicalReconstructionFilterTest, middleIsntReconstructed) {
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

TEST(MorphologicalReconstructionFilterTest, markerSpreadsThroughSpiral) {
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
