#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeImage.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeImageNodeRemovalTest, pixelsAreUpdatedWhenNodeIsRemoved) {
    MaxTreeImage<SimpleArrayImage<DummyType> > image(2, 2);

    auto lowerPixelColor = DummyType{ 3018 };
    auto higherPixelColor = DummyType{ 91314 };

    image.setPixel(0, 0, lowerPixelColor);
    image.setPixel(1, 0, higherPixelColor);
    image.setPixel(0, 1, higherPixelColor);
    image.setPixel(1, 1, higherPixelColor);

    image.assignPixelToLatestNode(0, 0);
    image.assignPixelToLatestNode(1, 0);
    image.assignPixelToLatestNode(0, 1);
    image.assignPixelToLatestNode(1, 1);

    auto& higherNode = image.getPixelNode(1, 1);

    image.removeNode(higherNode);

    assertThat(image.getPixelValue(0, 0)).isEqualTo(lowerPixelColor);
    assertThat(image.getPixelValue(1, 0)).isEqualTo(lowerPixelColor);
    assertThat(image.getPixelValue(0, 1)).isEqualTo(lowerPixelColor);
    assertThat(image.getPixelValue(1, 1)).isEqualTo(lowerPixelColor);
}
