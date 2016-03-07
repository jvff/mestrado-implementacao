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

TEST_F(MinMaxTreeImageFilterImplementationTest, collectsThreeNodes) {
    auto firstPixelLevel = DummyType{ 892 };
    auto secondPixelLevel = DummyType{ 657 };
    auto thirdPixelLevel = DummyType{ 340 };

    auto sourceImage = ImageType(3, 1);
    auto destinationImage = ImageType(3, 1);
    auto implementation = FakeImplementationType(sourceImage, destinationImage);

    sourceImage.setPixel(0, 0, firstPixelLevel);
    sourceImage.setPixel(1, 0, secondPixelLevel);
    sourceImage.setPixel(2, 0, thirdPixelLevel);

    sourceImage.assignPixelToNewNode(0, 0);
    sourceImage.assignPixelToNewNode(1, 0);
    sourceImage.assignPixelToNewNode(2, 0);

    auto nodes = implementation.collectPixelNodes();

    assertThat(nodes.size()).isEqualTo(3u);

    auto position = nodes.begin();
    auto firstNode = *position;

    ++position;

    auto secondNode = *position;

    ++position;

    auto thirdNode = *position;

    assertThat(firstNode.getLevel()).isEqualTo(firstPixelLevel);
    assertThat(firstNode.getId()).isEqualTo(0u);

    assertThat(secondNode.getLevel()).isEqualTo(secondPixelLevel);
    assertThat(secondNode.getId()).isEqualTo(0u);

    assertThat(thirdNode.getLevel()).isEqualTo(thirdPixelLevel);
    assertThat(thirdNode.getId()).isEqualTo(0u);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, onlyAddsNodeOnce) {
    auto extremityPixelLevel = DummyType{ 892 };
    auto middlePixelLevel = DummyType{ 657 };

    auto sourceImage = ImageType(3, 1);
    auto destinationImage = ImageType(3, 1);
    auto implementation = FakeImplementationType(sourceImage, destinationImage);

    sourceImage.setPixel(0, 0, extremityPixelLevel);
    sourceImage.setPixel(1, 0, middlePixelLevel);
    sourceImage.setPixel(2, 0, extremityPixelLevel);

    sourceImage.assignPixelToNewNode(0, 0);
    sourceImage.assignPixelToNewNode(1, 0);
    sourceImage.assignPixelToLatestNode(2, 0);

    auto nodes = implementation.collectPixelNodes();

    assertThat(nodes.size()).isEqualTo(2u);

    auto position = nodes.begin();
    auto extremityNode = *position;

    ++position;

    auto middleNode = *position;

    assertThat(extremityNode.getLevel()).isEqualTo(extremityPixelLevel);
    assertThat(extremityNode.getId()).isEqualTo(0u);

    assertThat(middleNode.getLevel()).isEqualTo(middlePixelLevel);
    assertThat(middleNode.getId()).isEqualTo(0u);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, collectsNodesWithDifferentIds) {
    auto extremityPixelLevel = DummyType{ 892 };
    auto middlePixelLevel = DummyType{ 657 };

    auto sourceImage = ImageType(3, 1);
    auto destinationImage = ImageType(3, 1);
    auto implementation = FakeImplementationType(sourceImage, destinationImage);

    sourceImage.setPixel(0, 0, extremityPixelLevel);
    sourceImage.setPixel(1, 0, middlePixelLevel);
    sourceImage.setPixel(2, 0, extremityPixelLevel);

    sourceImage.assignPixelToNewNode(0, 0);
    sourceImage.assignPixelToNewNode(1, 0);
    sourceImage.assignPixelToNewNode(2, 0);

    auto nodes = implementation.collectPixelNodes();

    assertThat(nodes.size()).isEqualTo(3u);

    auto position = nodes.begin();
    auto firstNode = *position;

    ++position;

    auto secondNode = *position;

    ++position;

    auto thirdNode = *position;

    assertThat(firstNode.getLevel()).isEqualTo(extremityPixelLevel);
    assertThat(firstNode.getId()).isEqualTo(0u);

    assertThat(secondNode.getLevel()).isEqualTo(extremityPixelLevel);
    assertThat(secondNode.getId()).isEqualTo(1u);

    assertThat(thirdNode.getLevel()).isEqualTo(middlePixelLevel);
    assertThat(thirdNode.getId()).isEqualTo(0u);
}
