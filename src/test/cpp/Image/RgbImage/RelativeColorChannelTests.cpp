#include "AllRgbImagePixelTypes.hpp"
#include "RgbImageRelativeColorChannelTests.hpp"

TYPED_TEST_CASE(RgbImageRelativeColorChannelTests, PixelTypes);

TEST_C(hasRedGreenAndBlueRelativeValues) {
    const bool withoutAlpha = false;

    unsigned int width = 20;
    unsigned int height = 17;

    calculateChannelParameters();

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    checkRelativeChannelsOfAllPixels(internalImage, rgbImage, withoutAlpha);
}

TEST_C(hasRedGreenBlueAndAlphaRelativeValues) {
    const bool withAlpha = true;

    unsigned int width = 20;
    unsigned int height = 17;

    calculateChannelParameters(withAlpha);

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, withAlpha);

    checkRelativeChannelsOfAllPixels(internalImage, rgbImage, withAlpha);
}
