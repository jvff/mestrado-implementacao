#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MorphologicalGradientFilter.hpp"

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
