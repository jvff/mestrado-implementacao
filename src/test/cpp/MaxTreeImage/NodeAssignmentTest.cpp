#include "MaxTreeImageTest.hpp"

SUB_TEST(NodeAssignmentTest);

TEST_C(NodeAssignmentTest, allowsAssigningToRootNode) {
    unsigned int width = 3;
    unsigned int height = 2;
    PixelType rootNodeLevel = { 10 };

    DummyMaxTreeImageType image(width, height);

    fillImage(image, rootNodeLevel);
    assignPixelsToLatestNodes(image);

    auto expectedRootNode = makeNode(0u, rootNodeLevel);

    verifyNodes(image, expectedRootNode);
}

TEST_C(NodeAssignmentTest, nodeParentChain) {
    unsigned int width = 2;
    unsigned int height = 2;

    DummyMaxTreeImageType image(width, height);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    verifyNodes(image, [&] (unsigned int x, unsigned int y)
            -> TreeNodeType {
        TreeNodePointer parent;
        int level = x + y * width;

        for (auto parentLevel = 0; parentLevel < level; ++parentLevel) {
            auto newParent = makeNode(0u, PixelType{ parentLevel }, parent);

            parent = newParent;
        }

        auto expectedNode = makeNode(0u, PixelType{ level }, parent);

        return *expectedNode;
    });
}

TEST_C(NodeAssignmentTest, forkingCreatesTreeBranch) {
    unsigned int width = 2;
    unsigned int height = 2;

    DummyMaxTreeImageType image(width, height);
    auto background = PixelType{ 100 };
    auto foreground = PixelType{ 1000 };

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
    DummyMaxTreeImageType image(3, 1);

    auto leftPixelColor = PixelType{ 14 };
    auto middlePixelColor = PixelType{ 16 };
    auto rightPixelColor = PixelType{ 15 };

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
    DummyMaxTreeImageType image(3, 1);

    auto leftPixelColor = PixelType{ 14 };
    auto middlePixelColor = PixelType{ 16 };
    auto rightPixelColor = PixelType{ 15 };

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
