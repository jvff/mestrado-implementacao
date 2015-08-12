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
