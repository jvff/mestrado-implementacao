#include "ComparisonTests.hpp"

PIXEL_TYPES(int, bool);

TEST_C(isComparable) {
    auto width = 89u;
    auto height = 78u;
    auto firstImage = createImage(width, height);
    auto secondImage = createImage(width, height);

    auto paintFunction = [&] (unsigned int x, unsigned int y) -> PixelType {
        return pattern(width, height, x, y);
    };

    firstImage = paintFunction;
    secondImage = paintFunction;

    assertThat(firstImage).isEqualTo(secondImage);
    assertThat(secondImage).isEqualTo(firstImage);
}
