#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalGradientFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MorphologicalGradientFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = MorphologicalGradientFilter<DummyType, DummyType,
            ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(MorphologicalGradientFilterTest, hasOptionalTemplateParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplicitType = MorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = MorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(MorphologicalGradientFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = MorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(MorphologicalGradientFilterTest, isConstructibleWithParameter) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = MorphologicalGradientFilter<DummyType, DummyType,
            ImageType>;
    using StructureSizeParameter = unsigned int;

    AssertThat<DummyFilter>::isConstructible(With<StructureSizeParameter>());
}

TEST(MorphologicalGradientFilterTest, binarySquare) {
    using PixelType = bool;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = MorphologicalGradientFilter<PixelType, PixelType,
            ImageType>;

    const unsigned int structureSize = 1;
    const unsigned int imageSize = 10;
    const unsigned int squareSize = 6;
    const unsigned int squareStart = (imageSize - squareSize) / 2;
    const unsigned int squareEnd = squareStart + squareSize;
    const unsigned int outerSquareStart = squareStart - structureSize;
    const unsigned int outerSquareEnd = squareEnd + structureSize;
    const unsigned int innerSquareStart = squareStart + structureSize;
    const unsigned int innerSquareEnd = squareEnd - structureSize;

    FilterType filter(structureSize);
    ImageType sourceImage(imageSize, imageSize);
    ImageType expectedImage(imageSize, imageSize);

    sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        return x >= squareStart && x < squareEnd && y >= squareStart
            && y < squareEnd;
    };

    expectedImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x >= innerSquareStart && x < innerSquareEnd && y >= innerSquareStart
                && y < innerSquareEnd) {
            return false;
        } else if (x >= outerSquareStart && x < outerSquareEnd
                && y >= outerSquareStart && y < outerSquareEnd) {
            return true;
        } else
            return false;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}
