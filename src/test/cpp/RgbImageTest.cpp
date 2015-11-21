#include "RgbImageTest.hpp"

using PixelTypes = ::testing::Types<unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long, char, short, int, long, long long,
        std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, std::int8_t,
        std::int16_t, std::int32_t, std::int64_t>;
TYPED_TEST_CASE(RgbImageTest, PixelTypes);

TYPED_TEST(RgbImageTest, classTemplateExists) {
    using RgbImageType = typename TestFixture::RgbImageType;

    AssertThat<RgbImageType>::isClassOrStruct();
}

TYPED_TEST(RgbImageTest, isSubClassOfImage) {
    using PixelType = typename TestFixture::PixelType;
    using RgbImageClass = typename TestFixture::RgbImageType;
    using ParentImageClass = Image<PixelType>;

    AssertThat<RgbImageClass>::isSubClass(Of<ParentImageClass>());
}

TYPED_TEST(RgbImageTest, isConstructibleWithUnsignedIntImage) {
    using InternalImageType = typename TestFixture::InternalImageType;
    using IntRgbImageClass = typename TestFixture::RgbImageType;
    using IntImageParameter = InternalImageType&;

    AssertThat<IntRgbImageClass>::isConstructible(With<IntImageParameter>());
}

TYPED_TEST(RgbImageTest, isConstructibleWithUnsignedIntImageAndAlphaFlag) {
    using InternalImageType = typename TestFixture::InternalImageType;
    using IntRgbImageClass = typename TestFixture::RgbImageType;
    using IntImageParameter = InternalImageType&;
    using HasAlphaFlag = bool;

    AssertThat<IntRgbImageClass>::isConstructible(
            With<IntImageParameter, HasAlphaFlag>());
}

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
    using PixelType = typename TestFixture::PixelType;
    using RgbImageType = typename TestFixture::RgbImageType;

    unsigned int width = 20;
    unsigned int height = 17;

    this->calculateChannelParameters();

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            PixelType pixelValue = internalImage.getPixelValue(x, y);

            auto expectedRedComponent = this->getRedComponentOf(pixelValue);
            auto expectedGreenComponent = this->getGreenComponentOf(pixelValue);
            auto expectedBlueComponent = this->getBlueComponentOf(pixelValue);

            PixelType redComponent = rgbImage.getRedComponent(x, y);
            PixelType greenComponent = rgbImage.getGreenComponent(x, y);
            PixelType blueComponent = rgbImage.getBlueComponent(x, y);

            assertThat(redComponent).isEqualTo(expectedRedComponent);
            assertThat(greenComponent).isEqualTo(expectedGreenComponent);
            assertThat(blueComponent).isEqualTo(expectedBlueComponent);
        }
    }
}

TYPED_TEST(RgbImageTest, hasRedGreenAndBlueRelativeValues) {
    using PixelType = typename TestFixture::PixelType;
    using RgbImageType = typename TestFixture::RgbImageType;

    unsigned int width = 20;
    unsigned int height = 17;

    this->calculateChannelParameters();

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            PixelType pixelValue = internalImage.getPixelValue(x, y);

            float expectedRedComponent =
                    this->getRelativeRedComponentOf(pixelValue);
            float expectedGreenComponent =
                    this->getRelativeGreenComponentOf(pixelValue);
            float expectedBlueComponent =
                    this->getRelativeBlueComponentOf(pixelValue);

            float redComponent = rgbImage.getRelativeRedComponent(x, y);
            float greenComponent = rgbImage.getRelativeGreenComponent(x, y);
            float blueComponent = rgbImage.getRelativeBlueComponent(x, y);

            assertThat(redComponent).isEqualTo(expectedRedComponent);
            assertThat(greenComponent).isEqualTo(expectedGreenComponent);
            assertThat(blueComponent).isEqualTo(expectedBlueComponent);
        }
    }
}

TYPED_TEST(RgbImageTest, hasRedGreenBlueAndAlphaChannels) {
    using PixelType = typename TestFixture::PixelType;
    using RgbImageType = typename TestFixture::RgbImageType;

    unsigned int width = 15;
    unsigned int height = 18;
    bool withAlpha = true;

    this->calculateChannelParameters(withAlpha);

    auto mockImage = this->mockColorInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage, withAlpha);

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            PixelType pixelValue = internalImage.getPixelValue(x, y);

            auto expectedRedComponent = this->getRedComponentOf(pixelValue);
            auto expectedGreenComponent = this->getGreenComponentOf(pixelValue);
            auto expectedBlueComponent = this->getBlueComponentOf(pixelValue);
            auto expectedAlphaComponent = this->getAlphaComponentOf(pixelValue);

            PixelType redComponent = rgbImage.getRedComponent(x, y);
            PixelType greenComponent = rgbImage.getGreenComponent(x, y);
            PixelType blueComponent = rgbImage.getBlueComponent(x, y);
            PixelType alphaComponent = rgbImage.getAlphaComponent(x, y);

            assertThat(redComponent).isEqualTo(expectedRedComponent);
            assertThat(greenComponent).isEqualTo(expectedGreenComponent);
            assertThat(blueComponent).isEqualTo(expectedBlueComponent);
            assertThat(alphaComponent).isEqualTo(expectedAlphaComponent);
        }
    }
}
