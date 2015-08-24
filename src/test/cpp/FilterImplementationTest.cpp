#include <gtest/gtest.h>

#include "asserts.hpp"
#include "fakeit.hpp"

#include "FilterImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "FakeFilterImplementation.hpp"

using namespace fakeit;

TEST(FilterImplementationTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementationType = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST(FilterImplementationTest, storesImageReferences) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using FakeDummyImplementationType = FakeFilterImplementation<
            SourceImageType, DestinationImageType>;

    Mock<SourceImageType> sourceImageMock;
    Mock<DestinationImageType> destinationImageMock;
    const auto& sourceImage = sourceImageMock.get();
    auto& destinationImage = destinationImageMock.get();

    FakeDummyImplementationType implementation(sourceImage, destinationImage);

    const auto& storedSourceImage = implementation.getSourceImage();
    const auto& storedDestinationImage = implementation.getDestinationImage();

    assertThat(storedSourceImage).isAtSameAddressAs(sourceImage);
    assertThat(storedDestinationImage).isAtSameAddressAs(destinationImage);
}
