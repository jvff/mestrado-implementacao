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

    verifyNodeData(node, pixelLevel, 0u);
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

    verifyNodeData(firstNode, firstPixelLevel, 0u);
    verifyNodeData(secondNode, secondPixelLevel, 0u);
    verifyNodeData(thirdNode, thirdPixelLevel, 0u);
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

    verifyNodeData(extremityNode, extremityPixelLevel, 0u);
    verifyNodeData(middleNode, middlePixelLevel, 0u);
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

    verifyNodeData(firstNode, extremityPixelLevel, 0u);
    verifyNodeData(secondNode, extremityPixelLevel, 1u);
    verifyNodeData(thirdNode, middlePixelLevel, 0u);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, canSelectLeafNodes) {
    auto leafLevel = DummyType{ 1 };
    auto leafNodeId = 0u;

    auto sourceImage = ImageType(1, 1);
    auto destinationImage = ImageType(1, 1);
    auto implementation = FakeImplementationType(sourceImage, destinationImage);

    std::set<NodeType> allNodes;

    auto rootNode = makeNode(0u, DummyType{ 3 });
    auto middleNode = makeNode(0u, DummyType{ 2 }, rootNode);
    auto leafNode = makeNode(leafNodeId, leafLevel, middleNode);

    allNodes.insert(*rootNode);
    allNodes.insert(*middleNode);
    allNodes.insert(*leafNode);

    auto leafNodes = implementation.getLeafNodesIn(allNodes);

    assertThat(leafNodes.size()).isEqualTo(1u);

    auto firstPosition = leafNodes.begin();
    auto resultingLeafNode = *firstPosition;

    verifyNodeData(resultingLeafNode, leafLevel, leafNodeId);
}
