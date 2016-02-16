#include "MaxTreeImageRootNodeRemovalTest.hpp"

TEST_F(MaxTreeImageRootNodeRemovalTest, pixelsAreUpdatedWhenRootNodeIsRemoved) {
    DummyMaxTreeImageType image(2, 2);

    auto lowerPixelColor = PixelType{ 3018 };
    auto higherPixelColor = PixelType{ 91314 };

    fillImage(image, higherPixelColor);
    image.setPixel(0, 0, lowerPixelColor);
    image.setPixel(0, 1, lowerPixelColor);

    assignPixelsToLatestNodes(image);

    auto& higherNode = image.getPixelNode(0, 0);

    image.removeNode(higherNode);

    verifyFilledImagePixels(image, higherPixelColor);
}

TEST_F(MaxTreeImageRootNodeRemovalTest,
        pixelNodeIdsAreUpdatedOnRootNodeRemoval) {
    DummyMaxTreeImageType image(3, 2);

    paintImage(image);

    auto newRootLevel = image.getPixelValue(1, 0).value;

    image.setPixel(2, 0, PixelType{ newRootLevel });

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 0);
    image.assignPixelToNewNode(2, 0);
    image.assignPixelToLatestNode(0, 1);
    image.assignPixelToLatestNode(1, 1);
    image.assignPixelToLatestNode(2, 1);

    auto& node = image.getPixelNode(0, 0);

    image.removeNode(node);

    verifyNode(image.getPixelNode(0, 0),
            PixelType{ 1 }, 0u);
    verifyNode(image.getPixelNode(1, 0),
            PixelType{ 1 }, 0u);
    verifyNode(image.getPixelNode(2, 0),
            PixelType{ 1 }, 0u);
    verifyNode(image.getPixelNode(0, 1),
            PixelType{ 3 }, 0u,
            PixelType{ 1 }, 0u);
    verifyNode(image.getPixelNode(1, 1),
            PixelType{ 4 }, 0u,
            PixelType{ 3 }, 0u,
            PixelType{ 1 }, 0u);
    verifyNode(image.getPixelNode(2, 1),
            PixelType{ 5 }, 0u,
            PixelType{ 4 }, 0u,
            PixelType{ 3 }, 0u,
            PixelType{ 1 }, 0u);
}
