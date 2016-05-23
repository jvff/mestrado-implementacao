#include "ImageImplementationTests.hpp"

PIXEL_TYPES(int, bool);

TEST_C(pixelsAreCorrect) {
    const auto width = 26u;
    const auto height = 17u;

    PixelType pixelValues[width * height];
    PixelType* pixelIterator = &pixelValues[0];

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y) {
            *pixelIterator = pattern(width, height, x, y);

            ++pixelIterator;
        }
    }

    testPixels(width, height, pixelValues);
}

TEST_C(isSettableWithLambdaExpression) {
    const auto width = 15u;
    const auto height = 22u;

    auto lambdaFunction = [&] (unsigned int x, unsigned int y) -> PixelType {
        return pattern(width, height, x, y);
    };

    testPixelsUsingLambda(width, height, lambdaFunction);
}
