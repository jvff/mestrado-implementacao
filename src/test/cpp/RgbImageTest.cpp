#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

using namespace fakeit;

TEST(RgbImageTest, classTemplateExists) {
    using InternalImageType = FakeImage<unsigned int>;
    using DummyRgbImage = RgbImage<InternalImageType>;

    AssertThat<DummyRgbImage>::isClassOrStruct();
}

TEST(RgbImageTest, isSubClassOfImage) {
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageClass = RgbImage<InternalImageType>;
    using ParentImageClass = Image<PixelType>;

    AssertThat<RgbImageClass>::isSubClass(Of<ParentImageClass>());
}

TEST(RgbImageTest, isConstructibleWithUnsignedIntImage) {
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;
    using IntRgbImageClass = RgbImage<InternalImageType>;
    using IntImageParameter = InternalImageType&;

    AssertThat<IntRgbImageClass>::isConstructible(With<IntImageParameter>());
}

TEST(RgbImageTest, usesInternalImage) {
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;

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

    RgbImage<InternalImageType> rgbImage(internalImage);

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
