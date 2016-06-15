#include "AllRgbImagePixelTypes.hpp"
#include "RgbImageRelativeColorChannelTests.hpp"

TYPED_TEST_CASE(RgbImageRelativeColorChannelTests, PixelTypes);

TEST_C(hasRedGreenAndBlueRelativeValues) {
    const bool withoutAlpha = false;

    unsigned int width = 20;
    unsigned int height = 17;

    initializePainter(width, height, withoutAlpha);

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    checkRelativeChannelsOfAllPixels(internalImage, rgbImage, withoutAlpha);
}

TEST_C(hasRedGreenBlueAndAlphaRelativeValues) {
    const bool withAlpha = true;

    unsigned int width = 20;
    unsigned int height = 17;

    initializePainter(width, height, withAlpha);

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, withAlpha);

    checkRelativeChannelsOfAllPixels(internalImage, rgbImage, withAlpha);
}

TEST_C(pixelsCanBeSetUsingRelativeComponents) {
    unsigned int width = 10;
    unsigned int height = 14;

    initializePainter(width, height);

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    auto rgbImage = RgbImageType(internalImage);

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y) {
            auto redComponent = painter->getRedComponent(x, y);
            auto greenComponent = painter->getGreenComponent(x, y);
            auto blueComponent = painter->getBlueComponent(x, y);

            rgbImage.setPixel(x, y, redComponent, greenComponent,
                    blueComponent);
        }
    }

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y) {
            auto& paintFunction = *painter;
            auto rawPixelValue = paintFunction(x, y);

            Verify(Method(mockImage, setPixel).Using(x, y, rawPixelValue));
        }
    }
}
