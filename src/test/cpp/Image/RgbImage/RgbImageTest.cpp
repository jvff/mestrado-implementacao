#include "RgbImageTest.hpp"

using PixelTypes = ::testing::Types<unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long, char, short, int, long, long long,
        std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, std::int8_t,
        std::int16_t, std::int32_t, std::int64_t>;
TYPED_TEST_CASE(RgbImageTest, PixelTypes);

TYPED_TEST(RgbImageTest, usesInternalImage) {
    using RgbImageType = typename TestFixture::RgbImageType;

    unsigned int width = 8;
    unsigned int height = 5;

    auto mockImage = this->mockSimpleInternalImage(width, height);
    auto& internalImage = mockImage.get();

    RgbImageType rgbImage(internalImage);

    assertThat(rgbImage.getWidth()).isEqualTo(width);
    assertThat(rgbImage.getHeight()).isEqualTo(height);

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto pixelValue = rgbImage.getPixelValue(x, y);
            auto expectedValue = internalImage.getPixelValue(x, y);

            assertThat(pixelValue).isEqualTo(expectedValue);
        }
    }
}

TYPED_TEST(RgbImageTest, updatesInternalImage) {
    using PixelType = typename TestFixture::PixelType;
    using RgbImageType = typename TestFixture::RgbImageType;

    unsigned int width = 4;
    unsigned int height = 7;

    auto mockImage = this->mockSimpleInternalImage(width, height);
    auto& internalImage = mockImage.get();

    RgbImageType rgbImage(internalImage);

    rgbImage = [height] (unsigned int x, unsigned int y) -> PixelType {
        return y + x * height;
    };

    assertThat(rgbImage.getWidth()).isEqualTo(width);
    assertThat(rgbImage.getHeight()).isEqualTo(height);

    PixelType pixelValue = 0;

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            Verify(Method(mockImage, setPixel).Using(x, y, pixelValue));

            ++pixelValue;
        }
    }
}

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
