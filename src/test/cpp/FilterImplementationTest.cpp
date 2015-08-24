#include "FilterImplementationTest.hpp"

TEST_F(FilterImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST_F(FilterImplementationTest, storesImageReferences) {
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
