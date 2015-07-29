#include <gtest/gtest.h>

#include "asserts.hpp"

#include "WatershedFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(WatershedFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = WatershedFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(WatershedFilterTest, defaultSourceImageTypeIsGenericImage) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using ImplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType>;
    using ExplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}
