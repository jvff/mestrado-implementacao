#include "MaxTreeImageComparisonTest.hpp"

TEST_F(MaxTreeImageComparisonTest, imagesAreComparable) {
    unsigned int width = 3;
    unsigned int height = 7;

    DummyMaxTreeImageType firstImage(width, height);
    DummyMaxTreeImageType secondImage(width, height);

    assertThat(firstImage).isEqualTo(secondImage);
}

TEST_F(MaxTreeImageComparisonTest, imagesWithDifferentWidthsArentEqual) {
    unsigned int firstWidth = 3;
    unsigned int secondWidth = 4;
    unsigned int height = 7;

    DummyMaxTreeImageType firstImage(firstWidth, height);
    DummyMaxTreeImageType secondImage(secondWidth, height);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(MaxTreeImageComparisonTest, imagesWithDifferentHeightsArentEqual) {
    unsigned int width = 3;
    unsigned int firstHeight = 4;
    unsigned int secondHeight = 7;

    DummyMaxTreeImageType firstImage(width, firstHeight);
    DummyMaxTreeImageType secondImage(width, secondHeight);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(MaxTreeImageComparisonTest, imagesWithDifferentPixelsAtZeroZeroArentEqual) {
    unsigned int width = 4;
    unsigned int height = 3;

    auto firstImage = DummyMaxTreeImageType(width, height);
    auto secondImage = DummyMaxTreeImageType(width, height);

    auto painter = [height] (unsigned int x, unsigned int y) -> PixelType {
        return PixelType{ (int)(y + x * height) };
    };

    firstImage = painter;
    secondImage = painter;

    secondImage.setPixel(0, 0, PixelType{ (int)(width * height) });

    assertThat(firstImage).isNotEqualTo(secondImage);
}
