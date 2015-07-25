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
    using PixelType = unsigned char;

    const PixelType depth = 10;
    const unsigned int width = 5;
    const unsigned int height = 3;

    TestData<PixelType> test(width, height);

    test.sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxX = width - 1;

        if (x >= 1 && x < maxX && y == height / 2)
            return 100;
        else
            return 0;
    };

    test.setMarker(0, std::make_tuple(1, height / 2, depth));

    test.expectedImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxX = width - 1;

        if (x >= 1 && x < maxX && y == height / 2)
            return depth;
        else
            return 0;
    };

    test.applyFilterAndVerifyResult();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsDown) {
    using PixelType = unsigned char;

    const PixelType depth = 10;
    const unsigned int width = 3;
    const unsigned int height = 5;

    TestData<PixelType> test(width, height);

    test.sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxY = height - 1;

        if (y >= 1 && y < maxY && x == width / 2)
            return 100;
        else
            return 0;
    };

    test.setMarker(0, std::make_tuple(width / 2, 1, depth));

    test.expectedImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxY = height - 1;

        if (y >= 1 && y < maxY && x == width / 2)
            return depth;
        else
            return 0;
    };

    test.applyFilterAndVerifyResult();
}

TEST(MorphologicalReconstructionFilterTest, markerSpreadsRightAndDown) {
    using PixelType = unsigned char;

    const PixelType depth = 33;
    const unsigned int width = 5;
    const unsigned int height = 5;

    TestData<PixelType> test(width, height);

    test.sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxX = width - 1;
        unsigned int maxY = height - 1;

        if (x >= 1 && x < maxX && y >= 1 && y < maxY)
            return 92;
        else
            return 0;
    };

    test.setMarker(0, std::make_tuple(1, 1, depth));

    test.expectedImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxX = width - 1;
        unsigned int maxY = height - 1;

        if (x >= 1 && x < maxX && y >= 1 && y < maxY)
            return depth;
        else
            return 0;
    };

    test.applyFilterAndVerifyResult();
}
