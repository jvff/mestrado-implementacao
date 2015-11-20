#ifndef RGB_IMAGE_TEST_HPP
#define RGB_IMAGE_TEST_HPP

#include <cmath>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "FakeImage.hpp"

using namespace fakeit;

class RgbImageTest : public ::testing::Test {
protected:
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageType = RgbImage<InternalImageType>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;

    const unsigned int totalBitDepth = sizeof(PixelType) * 8;
    const unsigned int bitDepth = totalBitDepth / 3;
    const unsigned int redChannelBitDepth = bitDepth;
    const unsigned int greenChannelBitDepth = totalBitDepth - 2 * bitDepth;
    const unsigned int blueChannelBitDepth = bitDepth;

    const unsigned int maxRedValue = (1 << redChannelBitDepth) - 1;
    const unsigned int maxGreenValue = (1 << blueChannelBitDepth) - 1;
    const unsigned int maxBlueValue = (1 << blueChannelBitDepth) - 1;

    const unsigned int redChannelMask = maxRedValue;
    const unsigned int greenChannelMask = maxGreenValue;
    const unsigned int blueChannelMask = maxBlueValue;

protected:
    Mock<InternalImageType> mockSimpleInternalImage(unsigned int width,
            unsigned int height) {
        return mockInternalImage(width, height, getSimplePaintFunction(width));
    }

    Mock<InternalImageType> mockColorInternalImage(unsigned int width,
            unsigned int height) {
        auto paintFunction = getColorPaintFunction(width, height);

        return mockInternalImage(width, height, paintFunction);
    }

    Mock<InternalImageType> mockInternalImage(unsigned int width,
            unsigned int height, PaintFunction paintFunction) {
        Mock<InternalImageType> mockImage;

        auto returnPixel = paintFunction;

        When(Method(mockImage, getWidth)).AlwaysReturn(width);
        When(Method(mockImage, getHeight)).AlwaysReturn(height);
        When(Method(mockImage, getPixelValue)).AlwaysDo(returnPixel);
        When(Method(mockImage, setPixel).Using(Lt(width), Lt(height), _))
            .AlwaysReturn();

        return mockImage;
    }

    PaintFunction getSimplePaintFunction(unsigned int width) {
        return [width] (unsigned int x, unsigned int y) -> PixelType {
            return x + y * width;
        };
    }

    PaintFunction getColorPaintFunction(unsigned int width,
            unsigned int height) {
        Coordinate topLeftCorner(0, 0);
        Coordinate topRightCorner(width - 1, 0);
        Coordinate bottomLeftCorner(0, height - 1);
        Coordinate bottomRightCorner(width - 1, height - 1);

        float maxDistance = topLeftCorner.distanceTo(bottomRightCorner) / 2.f;
        float conversionFactor = 1.f / maxDistance;

        return [=] (unsigned int x, unsigned int y) -> PixelType {
            Coordinate coordinate(x, y);

            auto distanceToTopLeftCorner = coordinate.distanceTo(topLeftCorner);

            float redComponent = std::min(distanceToTopLeftCorner,
                    coordinate.distanceTo(topRightCorner));
            float greenComponent = std::min(distanceToTopLeftCorner,
                    coordinate.distanceTo(bottomLeftCorner));
            float blueComponent = std::min(distanceToTopLeftCorner,
                    coordinate.distanceTo(bottomRightCorner));

            redComponent = 1.f - redComponent * conversionFactor;
            greenComponent = 1.f - greenComponent * conversionFactor;
            blueComponent = 1.f - blueComponent * conversionFactor;

            return makePixelValue(redComponent, greenComponent, blueComponent);
        };
    }

    PixelType makePixelValue(float redComponent, float greenComponent,
            float blueComponent) {
        PixelType pixel = 0;

        redComponent = std::max(1.f, std::abs(redComponent));
        greenComponent = std::max(1.f, std::abs(greenComponent));
        blueComponent = std::max(1.f, std::abs(blueComponent));

        redComponent *= maxRedValue;
        greenComponent *= maxGreenValue;
        blueComponent *= maxBlueValue;

        pixel |= ((PixelType)redComponent) & redChannelMask;
        pixel <<= redChannelBitDepth;

        pixel |= ((PixelType)greenComponent) & greenChannelMask;
        pixel <<= greenChannelBitDepth;

        pixel |= ((PixelType)blueComponent) & blueChannelMask;
        pixel <<= blueChannelBitDepth;

        return pixel;
    }

    PixelType getRedComponentOf(PixelType value) {
        unsigned int shiftAmount = greenChannelBitDepth + blueChannelBitDepth;

        return getColorComponent(value, shiftAmount, redChannelMask);
    }

    PixelType getGreenComponentOf(PixelType value) {
        unsigned int shiftAmount = blueChannelBitDepth;

        return getColorComponent(value, shiftAmount, greenChannelMask);
    }

    PixelType getBlueComponentOf(PixelType value) {
        unsigned int shiftAmount = 0;

        return getColorComponent(value, shiftAmount, blueChannelMask);
    }

    PixelType getColorComponent(PixelType value, unsigned int shiftAmount,
            unsigned int mask) {
        return (value >> shiftAmount) & mask;
    }
};

#endif
