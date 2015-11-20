#include "RgbImageTest.hpp"

using namespace fakeit;

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

    Mock<InternalImageType> mockImage;
    InternalImageType& internalImage = mockImage.get();

    auto returnPixel = [width] (unsigned int x, unsigned int y) -> PixelType {
        return y * width + x;
    };

    When(Method(mockImage, getWidth)).AlwaysReturn(width);
    When(Method(mockImage, getHeight)).AlwaysReturn(height);
    When(Method(mockImage, getPixelValue)).AlwaysDo(returnPixel);

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
