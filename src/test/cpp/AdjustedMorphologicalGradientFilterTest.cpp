#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AdjustedMorphologicalGradientFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AdjustedMorphologicalGradientFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AdjustedMorphologicalGradientFilter<DummyType,
            DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(AdjustedMorphologicalGradientFilterTest, hasOptionalTemplateParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplicitType = AdjustedMorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = AdjustedMorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(AdjustedMorphologicalGradientFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = AdjustedMorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(AdjustedMorphologicalGradientFilterTest, isConstructibleWithParameters) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using ImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = AdjustedMorphologicalGradientFilter<SourcePixelType,
            DestinationPixelType, ImageType>;
    using StructureSizeParameter = unsigned int;
    using ThresholdParameter = const SourcePixelType&;
    using MaxPixelValueParameter = const DestinationPixelType&;
    using AdjustmentExponentParameter = float;

    AssertThat<DummyFilter>::isConstructible(With<StructureSizeParameter,
            ThresholdParameter, MaxPixelValueParameter,
            AdjustmentExponentParameter>());
}

TEST(AdjustedMorphologicalGradientFilterTest, lightSquare) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = AdjustedMorphologicalGradientFilter<PixelType, PixelType,
            ImageType>;

    const unsigned int structureSize = 1;
    const PixelType activationThreshold = 1;
    const PixelType maxPixelValue = 0xFF;
    const float adjustmentExponent = 0.01;

    const unsigned int imageSize = 10;
    const unsigned int squareSize = 6;
    const unsigned int squareStart = 2;
    const unsigned int squareEnd = squareStart + squareSize - 1;
    const unsigned int outerSquareStart = squareStart - structureSize;
    const unsigned int outerSquareEnd = squareEnd + structureSize;
    const unsigned int innerSquareStart = squareStart + structureSize;
    const unsigned int innerSquareEnd = squareEnd - structureSize;

    FilterType filter(structureSize, activationThreshold, maxPixelValue,
            adjustmentExponent);
    ImageType sourceImage(imageSize, imageSize);
    ImageType expectedImage(imageSize, imageSize);

    sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x >= squareStart && x <= squareEnd && y >= squareStart
                && y <= squareEnd) {
            return 100;
        } else
            return 50;
    };

    expectedImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x >= innerSquareStart && x <= innerSquareEnd
                && y >= innerSquareStart && y <= innerSquareEnd) {
            return 0;
        } else if (x >= outerSquareStart && x <= outerSquareEnd
                && y >= outerSquareStart && y <= outerSquareEnd) {
            return 50;
        } else
            return 0;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}

TEST(AdjustedMorphologicalGradientFilterTest, darkSquare) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = AdjustedMorphologicalGradientFilter<PixelType, PixelType,
            ImageType>;

    const unsigned int structureSize = 1;
    const PixelType activationThreshold = 200;
    const PixelType maxPixelValue = 0xFF;
    const float adjustmentExponent = 0.01;

    const unsigned int imageSize = 10;
    const unsigned int squareSize = 6;
    const unsigned int squareStart = 2;
    const unsigned int squareEnd = squareStart + squareSize - 1;
    const unsigned int outerSquareStart = squareStart - structureSize;
    const unsigned int outerSquareEnd = squareEnd + structureSize;
    const unsigned int innerSquareStart = squareStart + structureSize;
    const unsigned int innerSquareEnd = squareEnd - structureSize;

    FilterType filter(structureSize, activationThreshold, maxPixelValue,
            adjustmentExponent);
    ImageType sourceImage(imageSize, imageSize);
    ImageType expectedImage(imageSize, imageSize);

    sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x >= squareStart && x <= squareEnd && y >= squareStart
                && y <= squareEnd) {
            return 100;
        } else
            return 50;
    };

    expectedImage = [=] (unsigned int x, unsigned int y) -> PixelType {
        if (x >= innerSquareStart && x <= innerSquareEnd
                && y >= innerSquareStart && y <= innerSquareEnd) {
            return 0;
        } else if (x >= outerSquareStart && x <= outerSquareEnd
                && y >= outerSquareStart && y <= outerSquareEnd) {
            float factor = (float)maxPixelValue;
            float unadjustedValue = 50.f;
            float unadjustedNormalizedValue = unadjustedValue / factor;
            float adjustedNormalizedValue = std::pow(unadjustedNormalizedValue,
                    adjustmentExponent);
            float adjustedValue = adjustedNormalizedValue * factor;

            return (PixelType)adjustedValue;
        } else
            return 0;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}
