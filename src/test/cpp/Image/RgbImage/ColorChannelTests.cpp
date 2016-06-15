#include "AllRgbImagePixelTypes.hpp"
#include "RgbImageColorChannelTests.hpp"

TYPED_TEST_CASE(RgbImageColorChannelTests, PixelTypes);

TEST_C(hasRedGreenAndBlueChannels) {
    unsigned int width = 20;
    unsigned int height = 17;

    calculateChannelParameters();

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    checkChannelsOfAllPixels(internalImage, rgbImage);
}

TEST_C(hasRedGreenBlueAndAlphaChannels) {
    const bool withAlpha = true;

    unsigned int width = 15;
    unsigned int height = 18;

    calculateChannelParameters(withAlpha);

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, withAlpha);

    checkChannelsOfAllPixels(internalImage, rgbImage);
}
