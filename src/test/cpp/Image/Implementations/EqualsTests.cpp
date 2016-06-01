#include "AllPixelTypes.hpp"
#include "EqualsTests.hpp"

TEST_C(imageIsEqualToItself) {
    auto width = 12u;
    auto height = 10u;
    auto image = createImage(width, height);

    image = [&] (unsigned int x, unsigned int y) -> PixelType {
        return pattern(width, height, x, y);
    };

    assertThat(image).isEqualTo(image);
}

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
