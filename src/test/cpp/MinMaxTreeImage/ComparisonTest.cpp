#include "MinMaxTreeImageTest.hpp"

SUB_TEST(ComparisonTest);

TEST_C(ComparisonTest, imagesAreComparable) {
    unsigned int width = 3;
    unsigned int height = 7;

    DummyMinMaxTreeImageType firstImage(width, height);
    DummyMinMaxTreeImageType secondImage(width, height);

    assignPixelsToLatestNodes(firstImage);
    assignPixelsToLatestNodes(secondImage);

    assertThat(firstImage).isEqualTo(secondImage);
}

TEST_C(ComparisonTest, imagesWithDifferentWidthsArentEqual) {
    unsigned int firstWidth = 3;
    unsigned int secondWidth = 4;
    unsigned int height = 7;

    DummyMinMaxTreeImageType firstImage(firstWidth, height);
    DummyMinMaxTreeImageType secondImage(secondWidth, height);

    assignPixelsToLatestNodes(firstImage);
    assignPixelsToLatestNodes(secondImage);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_C(ComparisonTest, imagesWithDifferentHeightsArentEqual) {
    unsigned int width = 3;
    unsigned int firstHeight = 4;
    unsigned int secondHeight = 7;

    DummyMinMaxTreeImageType firstImage(width, firstHeight);
    DummyMinMaxTreeImageType secondImage(width, secondHeight);

    assignPixelsToLatestNodes(firstImage);
    assignPixelsToLatestNodes(secondImage);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_C(ComparisonTest, imagesWithDifferentPixelsAtZeroZeroArentEqual) {
    unsigned int width = 4;
    unsigned int height = 3;

    auto firstImage = DummyMinMaxTreeImageType(width, height);
    auto secondImage = DummyMinMaxTreeImageType(width, height);

    auto painter = [height] (unsigned int x, unsigned int y) -> PixelType {
        return PixelType{ (int)(y + x * height) };
    };

    firstImage = painter;
    secondImage = painter;

    assignPixelsToLatestNodes(firstImage);
    assignPixelsToLatestNodes(secondImage);

    secondImage.setPixel(0, 0, PixelType{ (int)(width * height) });

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_C(ComparisonTest, imagesWithDifferentNodesArentEqual) {
    unsigned int width = 3;
    unsigned int height = 2;

    PixelType background = { 3 };
    PixelType foreground = { 7 };

    auto firstImage = DummyMinMaxTreeImageType(width, height);
    auto secondImage = DummyMinMaxTreeImageType(width, height);

    for (auto imagePointer : { &firstImage, &secondImage }) {
        *imagePointer = [background] (unsigned int, unsigned int) -> PixelType {
            return background;
        };

        imagePointer->setPixel(0, 0, foreground);
        imagePointer->setPixel(2, 0, foreground);

        imagePointer->assignPixelToLatestNode(1, 0);
        imagePointer->assignPixelToLatestNode(0, 1);
        imagePointer->assignPixelToLatestNode(1, 1);
        imagePointer->assignPixelToLatestNode(2, 1);
    }

    firstImage.assignPixelToLatestNode(0, 0);
    firstImage.assignPixelToNewNode(2, 0);

    secondImage.assignPixelToLatestNode(2, 0);
    secondImage.assignPixelToNewNode(0, 0);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_C(ComparisonTest, imagesWithDifferentNodeParentsArentEqual) {
    unsigned int width = 3;
    unsigned int height = 2;

    PixelType background = { 3 };
    PixelType middleground = { 5 };
    PixelType foreground = { 7 };

    auto firstImage = DummyMinMaxTreeImageType(width, height);
    auto secondImage = DummyMinMaxTreeImageType(width, height);

    for (auto imagePointer : { &firstImage, &secondImage }) {
        imagePointer->setPixel(0, 0, foreground);
        imagePointer->setPixel(1, 0, background);
        imagePointer->setPixel(2, 0, foreground);
        imagePointer->setPixel(0, 1, middleground);
        imagePointer->setPixel(1, 1, background);
        imagePointer->setPixel(2, 1, middleground);

        imagePointer->assignPixelToLatestNode(1, 0);
        imagePointer->assignPixelToLatestNode(1, 1);
    }

    firstImage.assignPixelToNewNode(0, 1);
    firstImage.assignPixelToNewNode(0, 0);
    firstImage.assignPixelToNewNode(2, 1);
    firstImage.assignPixelToNewNode(2, 0);

    secondImage.assignPixelToNewNode(0, 1);
    secondImage.assignPixelToNewNode(2, 1);
    secondImage.assignPixelToNewNode(2, 0);
    secondImage.assignPixelToLatestNode(0, 0);

    assertThat(firstImage).isNotEqualTo(secondImage);
}
