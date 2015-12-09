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

TEST_F(MaxTreeImageNodeRemovalTest, pixelNodeIdsAreUpdated) {
    auto width = 3u;

    DummyMaxTreeImageType image(width, 2);

    paintImage(image);

    auto levelToSkip = image.getPixelValue(2, 0).value;
    auto repeatedLevel = image.getPixelValue(1, 0).value;
    auto removedLevel = image.getPixelValue(0, 1).value;

    image.setPixel(2, 0, PixelType{ repeatedLevel });

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 0);
    image.assignPixelToNewNode(2, 0);
    image.assignPixelToLatestNode(0, 1);
    image.assignPixelToLatestNode(1, 1);
    image.assignPixelToLatestNode(2, 1);

    auto& node = image.getPixelNode(0, 1);

    image.removeNode(node);

    verifyNodes(image, [=] (unsigned int x, unsigned int y) -> TreeNodeType {
        if (x == 0 && y == 1) {
            x = 2;
            y = 0;
        }

        TreeNodePointer parent;
        auto pixelLevel = (int)(x + y * width);
        auto pixelNodeId = 0u;

        if (x == 2 && y == 0) {
            pixelLevel = 1;
            pixelNodeId = 1u;
        }

        for (auto level = 0; level < pixelLevel; ++level) {
            if (level != levelToSkip && level != removedLevel) {
                auto id = level == repeatedLevel ? 1u : 0u;
                auto node = makeNode(id, PixelType{ level }, parent);

                parent = node;
            }
        }

        return TreeNodeType(parent, PixelType{ pixelLevel }, pixelNodeId);
    });
}

TEST_F(MaxTreeImageNodeRemovalTest, pixelsAreUpdatedWhenRootNodeIsRemoved) {
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

TEST_F(MaxTreeImageNodeRemovalTest, pixelNodeIdsAreUpdatedOnRootNodeRemoval) {
    auto width = 3u;

    DummyMaxTreeImageType image(width, 2);

    paintImage(image);

    auto levelToSkip = image.getPixelValue(2, 0).value;
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

    verifyNodes(image, [=] (unsigned int x, unsigned int y) -> TreeNodeType {
        if (y == 0)
            x = 1;

        TreeNodePointer parent;
        auto pixelLevel = (int)(x + y * width);

        for (auto level = 1; level < pixelLevel; ++level) {
            if (level != levelToSkip) {
                auto node = makeNode(0u, PixelType{ level }, parent);

                parent = node;
            }
        }

        return TreeNodeType(parent, PixelType{ pixelLevel }, 0u);
    });
}
