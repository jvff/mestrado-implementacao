#include "MinMaxTreeImageTest.hpp"

SUB_TEST(NodeRemovalTest);

TEST_C(NodeRemovalTest, pixelsAreUpdatedWhenNodeIsRemoved) {
    DummyMinMaxTreeImageType image(2, 2);

    auto levelHeights = makeLevelHeights({ 3018, 91314 });
    auto lowerPixelColor = levelHeights[0];
    auto higherPixelColor = levelHeights[1];

    fillImage(image, higherPixelColor);
    image.setPixel(0, 0, lowerPixelColor);

    assignPixelsToLatestNodes(image);

    auto& higherNode = image.getPixelNode(1, 1);

    image.removeNode(higherNode);

    verifyFilledImagePixels(image, lowerPixelColor);
}

TEST_C(NodeRemovalTest, onlyPixelsAssignedToNodeAreUpdated) {
    DummyMinMaxTreeImageType image(2, 2);

    auto levelHeights = makeLevelHeights({ 3018, 91314 });
    auto lowerPixelColor = levelHeights[0];
    auto higherPixelColor = levelHeights[1];

    fillImage(image, higherPixelColor);
    image.setPixel(0, 0, lowerPixelColor);

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 0);
    image.assignPixelToNewNode(0, 1);
    image.assignPixelToLatestNode(1, 1);

    auto& higherNode = image.getPixelNode(1, 1);

    image.removeNode(higherNode);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(lowerPixelColor);
    assertThat(image.getPixelValue(1, 0)).isEqualTo(higherPixelColor);
    assertThat(image.getPixelValue(0, 1)).isEqualTo(lowerPixelColor);
    assertThat(image.getPixelValue(1, 1)).isEqualTo(lowerPixelColor);
}

TEST_C(NodeRemovalTest, treeIsUpdated) {
    auto levelHeights = makeLevelHeights({ 0, 1, 2, 3 });
    DummyMinMaxTreeImageType image(2, 2);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto& node = image.getPixelNode(0, 1);

    image.removeNode(node);

    verifyNode(image.getPixelNode(0, 0),
            levelHeights[0], 0u);
    verifyNode(image.getPixelNode(1, 0),
            levelHeights[1], 0u,
            levelHeights[0], 0u);
    verifyNode(image.getPixelNode(0, 1),
            levelHeights[1], 0u,
            levelHeights[0], 0u);
    verifyNode(image.getPixelNode(1, 1),
            levelHeights[3], 0u,
            levelHeights[1], 0u,
            levelHeights[0], 0u);
}

TEST_C(NodeRemovalTest, pixelNodeIdsAreUpdated) {
    auto levelHeights = makeLevelHeights({ 0, 1, 2, 3, 4, 5 });
    DummyMinMaxTreeImageType image(3, 2);

    paintImage(image);

    auto repeatedLevel = image.getPixelValue(1, 0);

    image.setPixel(2, 0, repeatedLevel);

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 0);
    image.assignPixelToNewNode(2, 0);
    image.assignPixelToLatestNode(0, 1);
    image.assignPixelToLatestNode(1, 1);
    image.assignPixelToLatestNode(2, 1);

    auto& node = image.getPixelNode(0, 1);

    image.removeNode(node);

    auto& firstNode = image.getPixelNode(0, 0);
    auto& secondNode = image.getPixelNode(1, 0);
    auto& thirdNode = image.getPixelNode(2, 0);
    auto& fourthNode = image.getPixelNode(0, 1);
    auto& fifthNode = image.getPixelNode(1, 1);
    auto& sixthNode = image.getPixelNode(2, 1);

    verifyNode(firstNode, levelHeights[0], 0u);
    verifyNode(secondNode, levelHeights[1], 0u, firstNode);
    verifyNode(thirdNode, levelHeights[1], 1u, firstNode);
    verifyNode(fourthNode, levelHeights[1], 1u, firstNode);
    verifyNode(fifthNode, levelHeights[4], 0u, fourthNode);
    verifyNode(sixthNode, levelHeights[5], 0u, fifthNode);
}

TEST_C(NodeRemovalTest, parentOfNodeParameterIsNotUsed) {
    auto levelHeights = makeLevelHeights({ 0, 1, 2 });
    DummyMinMaxTreeImageType image(3, 1);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto nodeCopy = image.getPixelNode(1, 0);
    auto fakeParent = makeNode(0u, PixelType { 98765 });

    nodeCopy.setParent(fakeParent);
    image.removeNode(nodeCopy);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(levelHeights[0]);
    assertThat(image.getPixelValue(1, 0)).isEqualTo(levelHeights[0]);
    assertThat(image.getPixelValue(2, 0)).isEqualTo(levelHeights[2]);

    auto& firstNode = image.getPixelNode(0, 0);
    auto& secondNode = image.getPixelNode(1, 0);
    auto& thirdNode = image.getPixelNode(2, 0);

    verifyNode(firstNode, levelHeights[0], 0u);
    verifyNode(secondNode, levelHeights[0], 0u);
    verifyNode(thirdNode, levelHeights[2], 0u, firstNode);
}

TEST_C(NodeRemovalTest, nodeParameterWithoutParentCanBeUsed) {
    auto levelHeights = makeLevelHeights({ 0, 1, 2, 3 });
    DummyMinMaxTreeImageType image(4, 1);
    std::shared_ptr<TreeNodeType> noParent;

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto nodeCopy = image.getPixelNode(2, 0);

    nodeCopy.setParent(noParent);
    image.removeNode(nodeCopy);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(levelHeights[0]);
    assertThat(image.getPixelValue(1, 0)).isEqualTo(levelHeights[1]);
    assertThat(image.getPixelValue(2, 0)).isEqualTo(levelHeights[1]);
    assertThat(image.getPixelValue(3, 0)).isEqualTo(levelHeights[3]);

    auto& firstNode = image.getPixelNode(0, 0);
    auto& secondNode = image.getPixelNode(1, 0);
    auto& thirdNode = image.getPixelNode(2, 0);
    auto& fourthNode = image.getPixelNode(3, 0);

    verifyNode(firstNode, levelHeights[0], 0u);
    verifyNode(secondNode, levelHeights[1], 0u, firstNode);
    verifyNode(thirdNode, levelHeights[1], 0u, firstNode);
    verifyNode(fourthNode, levelHeights[3], 0u, secondNode);
}

TEST_C(NodeRemovalTest, cantRemoveNodeFromInexistentLevel) {
    auto levelHeights = makeLevelHeights({ 0, 1, 2, 3 });
    DummyMinMaxTreeImageType image(4, 1);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto fakeNode = TreeNodeType(PixelType{ 4 }, 0u);

    image.removeNode(fakeNode);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(levelHeights[0]);
    assertThat(image.getPixelValue(1, 0)).isEqualTo(levelHeights[1]);
    assertThat(image.getPixelValue(2, 0)).isEqualTo(levelHeights[2]);
    assertThat(image.getPixelValue(3, 0)).isEqualTo(levelHeights[3]);

    auto& firstNode = image.getPixelNode(0, 0);
    auto& secondNode = image.getPixelNode(1, 0);
    auto& thirdNode = image.getPixelNode(2, 0);
    auto& fourthNode = image.getPixelNode(3, 0);

    verifyNode(firstNode, levelHeights[0], 0u);
    verifyNode(secondNode, levelHeights[1], 0u, firstNode);
    verifyNode(thirdNode, levelHeights[2], 0u, secondNode);
    verifyNode(fourthNode, levelHeights[3], 0u, thirdNode);
}
