#include "MaxTreeImageComparisonTest.hpp"

TEST_F(MaxTreeImageComparisonTest, imagesAreComparable) {
    unsigned int width = 3;
    unsigned int height = 7;

    DummyMaxTreeImageType firstImage(width, height);
    DummyMaxTreeImageType secondImage(width, height);

    createDefaultTreeFor(firstImage);
    createDefaultTreeFor(secondImage);

    assertThat(firstImage).isEqualTo(secondImage);
}

TEST_F(MaxTreeImageComparisonTest, imagesWithDifferentWidthsArentEqual) {
    unsigned int firstWidth = 3;
    unsigned int secondWidth = 4;
    unsigned int height = 7;

    DummyMaxTreeImageType firstImage(firstWidth, height);
    DummyMaxTreeImageType secondImage(secondWidth, height);

    createDefaultTreeFor(firstImage);
    createDefaultTreeFor(secondImage);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(MaxTreeImageComparisonTest, imagesWithDifferentHeightsArentEqual) {
    unsigned int width = 3;
    unsigned int firstHeight = 4;
    unsigned int secondHeight = 7;

    DummyMaxTreeImageType firstImage(width, firstHeight);
    DummyMaxTreeImageType secondImage(width, secondHeight);

    createDefaultTreeFor(firstImage);
    createDefaultTreeFor(secondImage);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(MaxTreeImageComparisonTest,
        imagesWithDifferentPixelsAtZeroZeroArentEqual) {
    unsigned int width = 4;
    unsigned int height = 3;

    auto firstImage = DummyMaxTreeImageType(width, height);
    auto secondImage = DummyMaxTreeImageType(width, height);

    auto painter = [height] (unsigned int x, unsigned int y) -> PixelType {
        return PixelType{ (int)(y + x * height) };
    };

    firstImage = painter;
    secondImage = painter;

    createDefaultTreeFor(firstImage);
    createDefaultTreeFor(secondImage);

    secondImage.setPixel(0, 0, PixelType{ (int)(width * height) });

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(MaxTreeImageComparisonTest, imagesWithDifferentNodesArentEqual) {
    unsigned int width = 3;
    unsigned int height = 2;

    PixelType background = { 3 };
    PixelType foreground = { 7 };

    auto firstImage = DummyMaxTreeImageType(width, height);
    auto secondImage = DummyMaxTreeImageType(width, height);

    auto painter = [background] (unsigned int, unsigned int) -> PixelType {
        return background;
    };

    firstImage = painter;
    secondImage = painter;

    firstImage.setPixel(0, 0, foreground);
    firstImage.setPixel(2, 0, foreground);

    secondImage.setPixel(0, 0, foreground);
    secondImage.setPixel(2, 0, foreground);

    firstImage.assignPixelToLatestNode(1, 0);
    firstImage.assignPixelToLatestNode(0, 1);
    firstImage.assignPixelToLatestNode(1, 1);
    firstImage.assignPixelToLatestNode(2, 1);

    secondImage.assignPixelToLatestNode(1, 0);
    secondImage.assignPixelToLatestNode(0, 1);
    secondImage.assignPixelToLatestNode(1, 1);
    secondImage.assignPixelToLatestNode(2, 1);

    firstImage.assignPixelToLatestNode(0, 0);
    firstImage.assignPixelToNewNode(2, 0);

    secondImage.assignPixelToNewNode(0, 0);
    secondImage.assignPixelToLatestNode(2, 0);

    assertThat(firstImage).isNotEqualTo(secondImage);
}
