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
