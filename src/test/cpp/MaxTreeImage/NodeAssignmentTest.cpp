#include "MaxTreeImageTest.hpp"

SUB_TEST(NodeAssignmentTest);

TEST_C(NodeAssignmentTest, allowsAssigningToRootNode) {
    unsigned int width = 3;
    unsigned int height = 2;
    PixelType rootNodeLevel = { 10 };

    DummyMinMaxTreeImageType image(width, height);

    fillImage(image, rootNodeLevel);
    assignPixelsToLatestNodes(image);

    auto expectedRootNode = makeNode(0u, rootNodeLevel);

    verifyNodes(image, expectedRootNode);
}

TEST_C(NodeAssignmentTest, nodeParentChain) {
    auto levelHeights = makeLevelHeights({ 0, 1, 2, 3 });

    unsigned int width = 2;
    unsigned int height = 2;

    DummyMinMaxTreeImageType image(width, height);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto firstPixelNode = image.getPixelNode(0, 0);
    auto secondPixelNode = image.getPixelNode(1, 0);
    auto thirdPixelNode = image.getPixelNode(0, 1);
    auto fourthPixelNode = image.getPixelNode(1, 1);

    verifyNode(firstPixelNode, levelHeights[0], 0u);
    verifyNode(secondPixelNode, levelHeights[1], 0u, firstPixelNode);
    verifyNode(thirdPixelNode, levelHeights[2], 0u, secondPixelNode);
    verifyNode(fourthPixelNode, levelHeights[3], 0u, thirdPixelNode);
}

TEST_C(NodeAssignmentTest, forkingCreatesTreeBranch) {
    unsigned int width = 2;
    unsigned int height = 2;

    DummyMinMaxTreeImageType image(width, height);
    auto levelHeights = makeLevelHeights({ 100, 1000 });
    auto background = levelHeights[0];
    auto foreground = levelHeights[1];

    image.setPixel(0, 0, background);
    image.setPixel(1, 0, foreground);
    image.setPixel(0, 1, foreground);
    image.setPixel(1, 1, background);

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 1);

    image.assignPixelToNewNode(1, 0);
    image.assignPixelToNewNode(0, 1);

    auto rootNode = makeNode(0u, background);

    verifyNodes(image, [=] (unsigned int x, unsigned int y) -> TreeNodeType {
        if (x == y)
            return *rootNode;
        else if (x == 1)
            return *makeNode(0u, foreground, rootNode);
        else
            return *makeNode(1u, foreground, rootNode);
    });
}

TEST_C(NodeAssignmentTest, separatedPartsOfRegionMayBeMislabeled) {
    DummyMinMaxTreeImageType image(3, 1);

    auto levelHeights = makeLevelHeights({ 14, 15, 16 });
    auto leftPixelColor = levelHeights[0];
    auto middlePixelColor = levelHeights[2];
    auto rightPixelColor = levelHeights[1];

    image.setPixel(0, 0, leftPixelColor);
    image.setPixel(1, 0, middlePixelColor);
    image.setPixel(2, 0, rightPixelColor);

    assignPixelsToLatestNodes(image);
    image.connectPixels(1, 0, 2, 0);

    auto leftPixelNode = makeNode(0u, leftPixelColor);
    auto rightPixelNode = makeNode(0u, rightPixelColor, leftPixelNode);
    auto middlePixelNode = makeNode(0u, middlePixelColor, rightPixelNode);

    verifyNode(image.getPixelNode(0, 0), *leftPixelNode);
    verifyNode(image.getPixelNode(1, 0), *middlePixelNode);
    verifyNode(image.getPixelNode(2, 0), *rightPixelNode);
}

TEST_C(NodeAssignmentTest, nodesAreMergedWhenPixelsAreConnected) {
    DummyMinMaxTreeImageType image(3, 1);

    auto levelHeights = makeLevelHeights({ 14, 15, 16 });
    auto leftPixelColor = levelHeights[0];
    auto middlePixelColor = levelHeights[2];
    auto rightPixelColor = levelHeights[1];

    image.setPixel(0, 0, leftPixelColor);
    image.setPixel(1, 0, middlePixelColor);
    image.setPixel(2, 0, rightPixelColor);

    assignPixelsToLatestNodes(image);

    auto leftPixelNode = makeNode(0u, leftPixelColor);
    auto middlePixelNode = makeNode(0u, middlePixelColor, leftPixelNode);
    auto rightPixelNode = makeNode(0u, rightPixelColor, leftPixelNode);

    verifyNode(image.getPixelNode(0, 0), leftPixelNode);
    verifyNode(image.getPixelNode(1, 0), middlePixelNode);
    verifyNode(image.getPixelNode(2, 0), rightPixelNode);
}
