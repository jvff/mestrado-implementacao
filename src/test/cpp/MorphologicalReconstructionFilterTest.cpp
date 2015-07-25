#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalReconstructionFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

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
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = MorphologicalReconstructionFilter<PixelType, ImageType>;

    const unsigned int width = 5;
    const unsigned int height = 3;
    const unsigned char depth = 10;

    FilterType filter;
    ImageType sourceImage(width, height);
    ImageType markerImage(width, height);
    ImageType expectedImage(width, height);

    sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxX = width - 1;

        if (x >= 1 && x < maxX && y == height / 2)
            return 100;
        else
            return 0;
    };

    markerImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x == 1 && y == height / 2)
            return depth;
        else
            return 0;
    };

    expectedImage = [] (unsigned int x, unsigned int y) -> PixelType {
        unsigned int maxX = width - 1;

        if (x >= 1 && x < maxX && y == height / 2)
            return depth;
        else
            return 0;
    };


    filter.apply(sourceImage, markerImage);

    assertThat(markerImage).isEqualTo(expectedImage);
}
