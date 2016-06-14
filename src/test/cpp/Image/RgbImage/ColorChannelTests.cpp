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

TEST_C(hasRedGreenAndBlueRelativeValues) {
    const bool WITHOUT_ALPHA = false;

    unsigned int width = 20;
    unsigned int height = 17;

    calculateChannelParameters();

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    checkRelativeChannelsOfAllPixels(internalImage, rgbImage, WITHOUT_ALPHA);
}

TEST_C(hasRedGreenBlueAndAlphaChannels) {
    unsigned int width = 15;
    unsigned int height = 18;
    bool withAlpha = true;

    calculateChannelParameters(withAlpha);

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, withAlpha);

    checkChannelsOfAllPixels(internalImage, rgbImage);
}

TEST_C(hasRedGreenBlueAndAlphaRelativeValues) {
    const bool WITH_ALPHA = true;

    unsigned int width = 20;
    unsigned int height = 17;

    calculateChannelParameters(WITH_ALPHA);

    auto mockImage = mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, WITH_ALPHA);

    checkRelativeChannelsOfAllPixels(internalImage, rgbImage, WITH_ALPHA);
}
