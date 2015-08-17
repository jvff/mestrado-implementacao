#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RegionalMaximumsFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(RegionalMaximumsFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = RegionalMaximumsFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(RegionalMaximumsFilterTest, hasOptionalTemplateParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplicitType = RegionalMaximumsFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = RegionalMaximumsFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}
