#include "AllRgbImagePixelTypes.hpp"
#include "RgbImageInternalImageTests.hpp"

TYPED_TEST_CASE(RgbImageInternalImageTests, PixelTypes);

TEST_C(internalImageCanBeAccessed) {
    unsigned int width = 2;
    unsigned int height = 4;

    auto mockImage = mockSimpleInternalImage(width, height);
    auto& internalImage = mockImage.get();

    RgbImageType rgbImage(internalImage);

    auto& retrievedInternalImage = rgbImage.getInternalImage();

    assertThat(retrievedInternalImage).isAtSameAddressAs(internalImage);
}

TEST_C(internalImageCanBeAccessedThroughConstObject) {
    unsigned int width = 2;
    unsigned int height = 4;

    auto mockImage = mockSimpleInternalImage(width, height);
    auto& internalImage = mockImage.get();

    const RgbImageType rgbImage(internalImage);

    auto& retrievedInternalImage = rgbImage.getInternalImage();

    using ResultType = decltype(retrievedInternalImage);

    assertThat<ResultType>(retrievedInternalImage).isConstReference();
    assertThat(retrievedInternalImage).isAtSameAddressAs(internalImage);
}

TEST_C(usesInternalImage) {
    unsigned int width = 8;
    unsigned int height = 5;

    auto mockImage = mockSimpleInternalImage(width, height);
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

TEST_C(updatesInternalImage) {
    unsigned int width = 4;
    unsigned int height = 7;

    auto mockImage = mockSimpleInternalImage(width, height);
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
