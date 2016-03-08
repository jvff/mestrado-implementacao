#include "MinMaxTreeImageFilterImplementationTest.hpp"

TEST_F(MinMaxTreeImageFilterImplementationTest, classTemplateExists) {
    AssertThat<ImplementationType>::isClassOrStruct();
}

TEST_F(MinMaxTreeImageFilterImplementationTest, isFilterImplementation) {
    using ParentImplementationType = FilterImplementation<ImageType, ImageType>;

    AssertThat<ImplementationType>::isSubClass(Of<ParentImplementationType>());
}

TEST_F(MinMaxTreeImageFilterImplementationTest, sourceImageIsAccessible) {
    assertThat(implementation->sourceImage).isAtSameAddressAs(*sourceImage);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, imageDimensionsAreAccessible) {
    auto width = 47u;
    auto height = 79u;

    initialize(width, height);

    assertThat(implementation->width).isEqualTo(width);
    assertThat(implementation->height).isEqualTo(height);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, canCollectNodes) {
    auto pixelLevel = DummyType{ 340 };

    sourceImage->setPixel(0, 0, pixelLevel);
    sourceImage->assignPixelToNewNode(0, 0);

    auto nodes = implementation->collectPixelNodes();

    verifyNodeSet(nodes, pixelLevel, 0u);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, collectsThreeNodes) {
    auto firstPixelLevel = DummyType{ 892 };
    auto secondPixelLevel = DummyType{ 657 };
    auto thirdPixelLevel = DummyType{ 340 };

    initialize(3, 1);

    sourceImage->setPixel(0, 0, firstPixelLevel);
    sourceImage->setPixel(1, 0, secondPixelLevel);
    sourceImage->setPixel(2, 0, thirdPixelLevel);

    sourceImage->assignPixelToNewNode(0, 0);
    sourceImage->assignPixelToNewNode(1, 0);
    sourceImage->assignPixelToNewNode(2, 0);

    auto nodes = implementation->collectPixelNodes();

    verifyNodeSet(nodes,
            firstPixelLevel, 0u,
            secondPixelLevel, 0u,
            thirdPixelLevel, 0u);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, onlyAddsNodeOnce) {
    auto extremityPixelLevel = DummyType{ 892 };
    auto middlePixelLevel = DummyType{ 657 };

    initialize(3, 1);

    sourceImage->setPixel(0, 0, extremityPixelLevel);
    sourceImage->setPixel(1, 0, middlePixelLevel);
    sourceImage->setPixel(2, 0, extremityPixelLevel);

    sourceImage->assignPixelToNewNode(0, 0);
    sourceImage->assignPixelToNewNode(1, 0);
    sourceImage->assignPixelToLatestNode(2, 0);

    auto nodes = implementation->collectPixelNodes();

    verifyNodeSet(nodes,
            extremityPixelLevel, 0u,
            middlePixelLevel, 0u);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, collectsNodesWithDifferentIds) {
    auto extremityPixelLevel = DummyType{ 892 };
    auto middlePixelLevel = DummyType{ 657 };

    initialize(3, 1);

    sourceImage->setPixel(0, 0, extremityPixelLevel);
    sourceImage->setPixel(1, 0, middlePixelLevel);
    sourceImage->setPixel(2, 0, extremityPixelLevel);

    sourceImage->assignPixelToNewNode(0, 0);
    sourceImage->assignPixelToNewNode(1, 0);
    sourceImage->assignPixelToNewNode(2, 0);

    auto nodes = implementation->collectPixelNodes();

    verifyNodeSet(nodes,
            extremityPixelLevel, 0u,
            extremityPixelLevel, 1u,
            middlePixelLevel, 0u);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, canSelectLeafNodes) {
    auto leafLevel = DummyType{ 1 };
    auto leafNodeId = 0u;

    std::set<NodeType> allNodes;

    auto rootNode = makeNode(0u, DummyType{ 3 });
    auto middleNode = makeNode(0u, DummyType{ 2 }, rootNode);
    auto leafNode = makeNode(leafNodeId, leafLevel, middleNode);

    allNodes.insert(*rootNode);
    allNodes.insert(*middleNode);
    allNodes.insert(*leafNode);

    auto leafNodes = implementation->getLeafNodesIn(allNodes);

    verifyNodeSet(leafNodes, leafLevel, leafNodeId);
}

TEST_F(MinMaxTreeImageFilterImplementationTest, selectsAllLeafNodes) {
    PixelType levelHeights[] = {
        PixelType{ 734 },
        PixelType{ 621 },
        PixelType{ 409 },
        PixelType{ 408 },
        PixelType{ 407 },
        PixelType{ 406 },
        PixelType{ 31 },
    };

    auto nodePointers = std::vector<NodePointer>({
        makeNode(0u, levelHeights[0]),
        makeNode(0u, levelHeights[1]),
        makeNode(0u, levelHeights[6]),
        makeNode(1u, levelHeights[6]),
        makeNode(1u, levelHeights[1]),
        makeNode(2u, levelHeights[1]),
        makeNode(0u, levelHeights[2]),
        makeNode(0u, levelHeights[3]),
        makeNode(0u, levelHeights[4]),
        makeNode(1u, levelHeights[3]),
        makeNode(1u, levelHeights[2]),
        makeNode(0u, levelHeights[5]),
        makeNode(2u, levelHeights[2]),
        makeNode(3u, levelHeights[2]),
    });

    nodePointers[1]->setParent(nodePointers[0]);
    nodePointers[4]->setParent(nodePointers[0]);
    nodePointers[5]->setParent(nodePointers[0]);

    nodePointers[2]->setParent(nodePointers[1]);
    nodePointers[3]->setParent(nodePointers[1]);

    nodePointers[6]->setParent(nodePointers[5]);
    nodePointers[10]->setParent(nodePointers[5]);
    nodePointers[12]->setParent(nodePointers[5]);
    nodePointers[13]->setParent(nodePointers[5]);

    nodePointers[7]->setParent(nodePointers[6]);
    nodePointers[9]->setParent(nodePointers[6]);

    nodePointers[8]->setParent(nodePointers[7]);

    nodePointers[11]->setParent(nodePointers[10]);

    std::set<NodeType> allNodes;

    for (auto& nodePointer : nodePointers)
        allNodes.insert(*nodePointer);

    auto leafNodes = implementation->getLeafNodesIn(allNodes);

    verifyNodeSet(leafNodes,
            nodePointers[4],
            nodePointers[12],
            nodePointers[13],
            nodePointers[9],
            nodePointers[8],
            nodePointers[11],
            nodePointers[2],
            nodePointers[3]);
}
