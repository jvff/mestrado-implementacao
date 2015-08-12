#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AdjustedMorphologicalGradientFilter.hpp"

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
