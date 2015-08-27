#include "FilterImplementationTest.hpp"

TEST_F(FilterImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST_F(FilterImplementationTest, hasApplyMethod) {
    assertThat(&DummyImplementationType::apply)
        .isMethod(WithSignature<void()>());
}

TEST_F(FilterImplementationTest, storesImageReferences) {
    Mock<SourceImageType> sourceImageMock;
    auto destinationImageMock = mockDestinationImage(15, 9);
    const auto& sourceImage = sourceImageMock.get();
    auto& destinationImage = destinationImageMock.get();

    FakeDummyImplementationType implementation(sourceImage, destinationImage);

    const auto& storedSourceImage = implementation.getSourceImage();
    const auto& storedDestinationImage = implementation.getDestinationImage();

    assertThat(storedSourceImage).isAtSameAddressAs(sourceImage);
    assertThat(storedDestinationImage).isAtSameAddressAs(destinationImage);
}

TEST_F(FilterImplementationTest, storesDestinationImageDimensions) {
    unsigned int width = 715;
    unsigned int height = 504;

    Mock<SourceImageType> sourceImageMock;
    auto destinationImageMock = mockDestinationImage(width, height);
    const auto& sourceImage = sourceImageMock.get();
    auto& destinationImage = destinationImageMock.get();

    FakeDummyImplementationType implementation(sourceImage, destinationImage);

    assertThat(implementation.getWidth()).isEqualTo(width);
    assertThat(implementation.getHeight()).isEqualTo(height);
}
