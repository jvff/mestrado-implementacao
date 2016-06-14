#include "AllRgbImagePixelTypes.hpp"
#include "RgbImageColorChannelTests.hpp"

TYPED_TEST_CASE(RgbImageColorChannelTests, PixelTypes);

TEST_C(hasRedGreenAndBlueChannels) {
    unsigned int width = 20;
    unsigned int height = 17;

    this->calculateChannelParameters();

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    this->checkChannelsOfAllPixels(internalImage, rgbImage);
}

TEST_C(hasRedGreenAndBlueRelativeValues) {
    const bool WITHOUT_ALPHA = false;

    unsigned int width = 20;
    unsigned int height = 17;

    this->calculateChannelParameters();

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    this->checkRelativeChannelsOfAllPixels(internalImage, rgbImage,
            WITHOUT_ALPHA);
}

TEST_C(hasRedGreenBlueAndAlphaChannels) {
    unsigned int width = 15;
    unsigned int height = 18;
    bool withAlpha = true;

    this->calculateChannelParameters(withAlpha);

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, withAlpha);

    this->checkChannelsOfAllPixels(internalImage, rgbImage);
}

TEST_C(hasRedGreenBlueAndAlphaRelativeValues) {
    const bool WITH_ALPHA = true;

    unsigned int width = 20;
    unsigned int height = 17;

    this->calculateChannelParameters(WITH_ALPHA);

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, WITH_ALPHA);

    this->checkRelativeChannelsOfAllPixels(internalImage, rgbImage, WITH_ALPHA);
}
