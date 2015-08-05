#include <gtest/gtest.h>

#include "asserts.hpp"

#include "WatershedImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(WatershedImplementationTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyImplementation = WatershedImplementation<DummyType, DummyType,
            ImageType>;

    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST(WatershedImplementationTest, defaultSourceImageTypeIsGenericImage) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using ImplicitType = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(WatershedImplementationTest, isConstructible) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using DummyImplementation = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(
            With<SourceImageParameter, DestinationImageParameter>());
}
