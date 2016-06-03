#include "AllPixelTypes.hpp"
#include "ComparisonTests.hpp"

TEST_C(imagesWithDifferentWidthsDiffer) {
    auto firstWidth = 23u;
    auto secondWidth = 22u;
    auto height = 10u;

    auto firstImage = createImage(firstWidth, height);
    auto secondImage = createImage(secondWidth, height);

    auto paintFunction = [&] (unsigned int x, unsigned int y) -> PixelType {
        return pattern(firstWidth, height, x, y);
    };

    firstImage = paintFunction;
    secondImage = paintFunction;

    assertThat(firstImage).isNotEqualTo(secondImage);
    assertThat(secondImage).isNotEqualTo(firstImage);
}

TEST_C(imagesWithDifferentHeightsDiffer) {
    auto width = 18u;
    auto firstHeight = 17u;
    auto secondHeight = 16u;

    auto firstImage = createImage(width, firstHeight);
    auto secondImage = createImage(width, secondHeight);

    auto paintFunction = [&] (unsigned int x, unsigned int y) -> PixelType {
        return pattern(width, firstHeight, x, y);
    };

    firstImage = paintFunction;
    secondImage = paintFunction;

    assertThat(firstImage).isNotEqualTo(secondImage);
    assertThat(secondImage).isNotEqualTo(firstImage);
}
