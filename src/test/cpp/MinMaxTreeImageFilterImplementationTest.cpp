#include "MinMaxTreeImageFilterImplementationTest.hpp"

TEST_F(MinMaxTreeImageFilterImplementationTest, classTemplateExists) {
    AssertThat<ImplementationType>::isClassOrStruct();
}

TEST_F(MinMaxTreeImageFilterImplementationTest, isFilterImplementation) {
    using ParentImplementationType = FilterImplementation<ImageType, ImageType>;

    AssertThat<ImplementationType>::isSubClass(Of<ParentImplementationType>());
}

TEST_F(MinMaxTreeImageFilterImplementationTest, canCollectNodes) {
    auto pixelLevel = DummyType{ 340 };
    auto sourceImage = ImageType(1, 1);
    auto destinationImage = ImageType(1, 1);
    auto implementation = FakeImplementationType(sourceImage, destinationImage);

    sourceImage.setPixel(0, 0, pixelLevel);
    sourceImage.assignPixelToNewNode(0, 0);

    auto nodes = implementation.collectPixelNodes();

    assertThat(nodes.size()).isEqualTo(1u);

    auto firstPosition = nodes.begin();
    auto node = *firstPosition;

    assertThat(node.getLevel()).isEqualTo(pixelLevel);
    assertThat(node.getId()).isEqualTo(0u);
}
