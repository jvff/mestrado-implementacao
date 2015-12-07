#include "MaxTreeImageNodeRemovalTest.hpp"

TEST_F(MaxTreeImageNodeRemovalTest, pixelsAreUpdatedWhenNodeIsRemoved) {
    DummyMaxTreeImageType image(2, 2);

    auto lowerPixelColor = PixelType{ 3018 };
    auto higherPixelColor = PixelType{ 91314 };

    fillImage(image, higherPixelColor);
    image.setPixel(0, 0, lowerPixelColor);

    assignPixelsToLatestNodes(image);

    auto& higherNode = image.getPixelNode(1, 1);

    image.removeNode(higherNode);

    verifyFilledImagePixels(image, lowerPixelColor);
}

TEST_F(MaxTreeImageNodeRemovalTest, onlyPixelsAssignedToNodeAreUpdated) {
    DummyMaxTreeImageType image(2, 2);

    auto lowerPixelColor = PixelType{ 3018 };
    auto higherPixelColor = PixelType{ 91314 };

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

TEST_F(MaxTreeImageNodeRemovalTest, treeIsUpdated) {
    auto width = 2u;

    DummyMaxTreeImageType image(width, 2);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto& node = image.getPixelNode(0, 1);

    image.removeNode(node);

    verifyNodes(image, [=] (unsigned int x, unsigned int y) -> TreeNodeType {
        if (x == 0 && y == 1) {
            x = 1;
            y = 0;
        }

        TreeNodePointer parent;
        auto pixelLevel = (int)(x + y * width);
        auto maxLevel = pixelLevel;

        if (x == 1 && y == 1)
            maxLevel -= 1;

        for (auto level = 0; level < maxLevel; ++level) {
            auto node = makeNode(0u, PixelType{ level }, parent);

            parent = node;
        }

        return TreeNodeType(parent, PixelType{ pixelLevel }, 0u);
    });
}
