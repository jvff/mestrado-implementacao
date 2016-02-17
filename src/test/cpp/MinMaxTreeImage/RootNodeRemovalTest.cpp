#include "MinMaxTreeImageTest.hpp"

SUB_TEST(RootNodeRemovalTest);

TEST_C(RootNodeRemovalTest, pixelsAreUpdatedWhenRootNodeIsRemoved) {
    DummyMinMaxTreeImageType image(2, 2);

    auto levelHeights = makeLevelHeights({ 3018, 91314 });
    auto lowerPixelColor = levelHeights[0];
    auto higherPixelColor = levelHeights[1];

    fillImage(image, higherPixelColor);
    image.setPixel(0, 0, lowerPixelColor);
    image.setPixel(0, 1, lowerPixelColor);

    assignPixelsToLatestNodes(image);

    auto& higherNode = image.getPixelNode(0, 0);

    image.removeNode(higherNode);

    verifyFilledImagePixels(image, higherPixelColor);
}

TEST_C(RootNodeRemovalTest, pixelNodeIdsAreUpdatedOnRootNodeRemoval) {
    DummyMinMaxTreeImageType image(3, 2);

    paintImage(image);

    auto levelHeights = makeLevelHeights({ 0, 1, 2, 3, 4, 5 });
    auto newRootLevel = levelHeights[1];

    image.setPixel(2, 0, newRootLevel);

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 0);
    image.assignPixelToNewNode(2, 0);
    image.assignPixelToLatestNode(0, 1);
    image.assignPixelToLatestNode(1, 1);
    image.assignPixelToLatestNode(2, 1);

    auto& node = image.getPixelNode(0, 0);

    image.removeNode(node);

    verifyNode(image.getPixelNode(0, 0),
            levelHeights[1], 0u);
    verifyNode(image.getPixelNode(1, 0),
            levelHeights[1], 0u);
    verifyNode(image.getPixelNode(2, 0),
            levelHeights[1], 0u);
    verifyNode(image.getPixelNode(0, 1),
            levelHeights[3], 0u,
            levelHeights[1], 0u);
    verifyNode(image.getPixelNode(1, 1),
            levelHeights[4], 0u,
            levelHeights[3], 0u,
            levelHeights[1], 0u);
    verifyNode(image.getPixelNode(2, 1),
            levelHeights[5], 0u,
            levelHeights[4], 0u,
            levelHeights[3], 0u,
            levelHeights[1], 0u);
}
