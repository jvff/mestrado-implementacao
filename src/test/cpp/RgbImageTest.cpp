#include "RgbImageTest.hpp"

TEST_F(RgbImageTest, classTemplateExists) {
    AssertThat<RgbImageType>::isClassOrStruct();
}

TEST_F(RgbImageTest, isSubClassOfImage) {
    using RgbImageClass = RgbImageType;
    using ParentImageClass = Image<PixelType>;

    AssertThat<RgbImageClass>::isSubClass(Of<ParentImageClass>());
}

TEST_F(RgbImageTest, isConstructibleWithUnsignedIntImage) {
    using IntRgbImageClass = RgbImageType;
    using IntImageParameter = InternalImageType&;

    AssertThat<IntRgbImageClass>::isConstructible(With<IntImageParameter>());
}

TEST_F(RgbImageTest, usesInternalImage) {
    unsigned int width = 8;
    unsigned int height = 5;

    auto mockImage = mockInternalImage(width, height);
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

TEST_F(RgbImageTest, updatesInternalImage) {
    unsigned int width = 4;
    unsigned int height = 7;

    auto mockImage = mockInternalImage(width, height);
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
