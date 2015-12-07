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
