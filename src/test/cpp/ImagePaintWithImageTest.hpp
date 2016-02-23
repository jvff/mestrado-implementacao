#ifndef IMAGE_PAINT_WITH_IMAGE_TEST_HPP
#define IMAGE_PAINT_WITH_IMAGE_TEST_HPP

#include <tuple>

#include <gtest/gtest.h>

#include "ImageTest.hpp"

struct ImageConfigurations {
    unsigned int sourceWidth;
    unsigned int sourceHeight;
    unsigned int destinationWidth;
    unsigned int destinationHeight;
};

class ImagePaintWithImageTest : public ImageTest,
        public testing::WithParamInterface<ImageConfigurations> {
protected:
    unsigned int sourceWidth;
    unsigned int sourceHeight;
    unsigned int destinationWidth;
    unsigned int destinationHeight;
    unsigned int smallestWidth;
    unsigned int smallestHeight;

public:
    void SetUp() {
        auto configurations = GetParam();

        sourceWidth = configurations.sourceWidth;
        sourceHeight = configurations.sourceHeight;
        destinationWidth = configurations.destinationWidth;
        destinationHeight = configurations.destinationHeight;

        smallestWidth = std::min(sourceWidth, destinationWidth);
        smallestHeight = std::min(sourceHeight, destinationHeight);
    }

protected:
    void verifyImageWasRead(Mock<FakeDummyImage>& mock) {
        for (unsigned int y = 0; y < smallestHeight; ++y) {
            for (unsigned int x = 0; x < smallestWidth; ++x)
                Verify(Method(mock, getPixelValue).Using(x, y));
        }

        VerifyNoOtherInvocations(Method(mock, getPixelValue));
    }

    void verifyImageWasPainted(Mock<FakeDummyImage>& mock) {
        auto pixelsToSkipAtEndOfRow = sourceWidth - smallestWidth;

        DummyType pixelValue = {0};

        for (unsigned int y = 0; y < smallestHeight; ++y) {
            for (unsigned int x = 0; x < smallestWidth; ++x) {
                Verify(Method(mock, setPixel).Using(x, y, pixelValue));

                ++pixelValue.value;
            }

            pixelValue.value += pixelsToSkipAtEndOfRow;
        }

        VerifyNoOtherInvocations(Method(mock, setPixel));
    }
};

#endif
