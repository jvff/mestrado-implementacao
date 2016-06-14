#include "RgbImageTest.hpp"

using PixelTypes = ::testing::Types<unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long, char, short, int, long, long long,
        std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, std::int8_t,
        std::int16_t, std::int32_t, std::int64_t>;
TYPED_TEST_CASE(RgbImageTest, PixelTypes);

TYPED_TEST(RgbImageTest, hasRedGreenAndBlueChannels) {
    using RgbImageType = typename TestFixture::RgbImageType;

    unsigned int width = 20;
    unsigned int height = 17;

    this->calculateChannelParameters();

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    this->checkChannelsOfAllPixels(internalImage, rgbImage);
}

TYPED_TEST(RgbImageTest, hasRedGreenAndBlueRelativeValues) {
    using RgbImageType = typename TestFixture::RgbImageType;

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

TYPED_TEST(RgbImageTest, hasRedGreenBlueAndAlphaChannels) {
    using RgbImageType = typename TestFixture::RgbImageType;

    unsigned int width = 15;
    unsigned int height = 18;
    bool withAlpha = true;

    this->calculateChannelParameters(withAlpha);

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, withAlpha);

    this->checkChannelsOfAllPixels(internalImage, rgbImage);
}

TYPED_TEST(RgbImageTest, hasRedGreenBlueAndAlphaRelativeValues) {
    using RgbImageType = typename TestFixture::RgbImageType;

    const bool WITH_ALPHA = true;

    unsigned int width = 20;
    unsigned int height = 17;

    this->calculateChannelParameters(WITH_ALPHA);

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, WITH_ALPHA);

    this->checkRelativeChannelsOfAllPixels(internalImage, rgbImage, WITH_ALPHA);
}
