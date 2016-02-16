#include "MaxTreeImageTest.hpp"

SUB_TEST(NodeRemovalTest);

TEST_C(NodeRemovalTest, pixelsAreUpdatedWhenNodeIsRemoved) {
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

TEST_C(NodeRemovalTest, onlyPixelsAssignedToNodeAreUpdated) {
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

TEST_C(NodeRemovalTest, treeIsUpdated) {
    DummyMaxTreeImageType image(2, 2);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto& node = image.getPixelNode(0, 1);

    image.removeNode(node);

    verifyNode(image.getPixelNode(0, 0),
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(1, 0),
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(0, 1),
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(1, 1),
            PixelType{ 3 }, 0u,
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
}

TEST_C(NodeRemovalTest, pixelNodeIdsAreUpdated) {
    DummyMaxTreeImageType image(3, 2);

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

    verifyNode(image.getPixelNode(0, 0),
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(1, 0),
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(2, 0),
            PixelType{ 1 }, 1u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(0, 1),
            PixelType{ 1 }, 1u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(1, 1),
            PixelType{ 4 }, 0u,
            PixelType{ 1 }, 1u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(2, 1),
            PixelType{ 5 }, 0u,
            PixelType{ 4 }, 0u,
            PixelType{ 1 }, 1u,
            PixelType{ 0 }, 0u);
}

TEST_C(NodeRemovalTest, parentOfNodeParameterIsNotUsed) {
    DummyMaxTreeImageType image(3, 1);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto nodeCopy = image.getPixelNode(1, 0);
    auto fakeParent = makeNode(0u, PixelType { 98765 });

    nodeCopy.setParent(fakeParent);
    image.removeNode(nodeCopy);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(PixelType{ 0 });
    assertThat(image.getPixelValue(1, 0)).isEqualTo(PixelType{ 0 });
    assertThat(image.getPixelValue(2, 0)).isEqualTo(PixelType{ 2 });

    verifyNode(image.getPixelNode(0, 0),
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(1, 0),
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(2, 0),
            PixelType{ 2 }, 0u,
            PixelType{ 0 }, 0u);
}

TEST_C(NodeRemovalTest, nodeParameterWithoutParentCanBeUsed) {
    DummyMaxTreeImageType image(4, 1);
    std::shared_ptr<TreeNodeType> noParent;

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto nodeCopy = image.getPixelNode(2, 0);

    nodeCopy.setParent(noParent);
    image.removeNode(nodeCopy);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(PixelType{ 0 });
    assertThat(image.getPixelValue(1, 0)).isEqualTo(PixelType{ 1 });
    assertThat(image.getPixelValue(2, 0)).isEqualTo(PixelType{ 1 });
    assertThat(image.getPixelValue(3, 0)).isEqualTo(PixelType{ 3 });

    verifyNode(image.getPixelNode(0, 0),
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(1, 0),
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(2, 0),
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(3, 0),
            PixelType{ 3 }, 0u,
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
}

TEST_C(NodeRemovalTest, cantRemoveNodeFromInexistentLevel) {
    DummyMaxTreeImageType image(4, 1);

    paintImage(image);
    assignPixelsToLatestNodes(image);

    auto fakeNode = TreeNodeType(PixelType{ 4 }, 0u);

    image.removeNode(fakeNode);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(PixelType{ 0 });
    assertThat(image.getPixelValue(1, 0)).isEqualTo(PixelType{ 1 });
    assertThat(image.getPixelValue(2, 0)).isEqualTo(PixelType{ 2 });
    assertThat(image.getPixelValue(3, 0)).isEqualTo(PixelType{ 3 });

    verifyNode(image.getPixelNode(0, 0),
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(1, 0),
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(2, 0),
            PixelType{ 2 }, 0u,
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
    verifyNode(image.getPixelNode(3, 0),
            PixelType{ 3 }, 0u,
            PixelType{ 2 }, 0u,
            PixelType{ 1 }, 0u,
            PixelType{ 0 }, 0u);
}
