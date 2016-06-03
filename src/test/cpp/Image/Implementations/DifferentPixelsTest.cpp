#include "AllPixelTypes.hpp"
#include "DifferentPixelsTest.hpp"

TEST_C(imagesWithDifferentPixelsDiffer) {
    auto width = 14u;
    auto height = 8u;

    auto firstImage = createImage(width, height);
    auto secondImage = createImage(width, height);

    firstImage = [&] (unsigned int x, unsigned int y) -> PixelType {
        return firstPattern(width, height, x, y);
    };

    secondImage = [&] (unsigned int x, unsigned int y) -> PixelType {
        return secondPattern(width, height, x, y);
    };

    assertThat(firstImage).isNotEqualTo(secondImage);
    assertThat(secondImage).isNotEqualTo(firstImage);
}
