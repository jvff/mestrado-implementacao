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

    unsigned int redChannelBitDepth;
    unsigned int greenChannelBitDepth;
    unsigned int blueChannelBitDepth;
    unsigned int alphaChannelBitDepth;

    unsigned int maxRedValue;
    unsigned int maxGreenValue;
    unsigned int maxBlueValue;
    unsigned int maxAlphaValue;

    unsigned int redChannelMask;
    unsigned int greenChannelMask;
    unsigned int blueChannelMask;
    unsigned int alphaChannelMask;

    unsigned int redChannelShiftAmount;
    unsigned int greenChannelShiftAmount;
    unsigned int blueChannelShiftAmount;
    unsigned int alphaChannelShiftAmount;

protected:
    void calculateChannelParameters(bool withAlpha = false) {
        unsigned int numChannels = withAlpha ? 4 : 3;
        unsigned int bitDepth = totalBitDepth / numChannels;

        redChannelBitDepth = bitDepth;
        greenChannelBitDepth = totalBitDepth - (numChannels - 1) * bitDepth;
        blueChannelBitDepth = bitDepth;
        alphaChannelBitDepth = withAlpha ? bitDepth : 0;

        maxRedValue = (1 << redChannelBitDepth) - 1;
        maxGreenValue = (1 << blueChannelBitDepth) - 1;
        maxBlueValue = (1 << blueChannelBitDepth) - 1;
        maxAlphaValue = (1 << alphaChannelBitDepth) - 1;

        redChannelMask = maxRedValue;
        greenChannelMask = maxGreenValue;
        blueChannelMask = maxBlueValue;
        alphaChannelMask = maxAlphaValue;

        alphaChannelShiftAmount = 0;
        blueChannelShiftAmount = alphaChannelShiftAmount + alphaChannelBitDepth;
        greenChannelShiftAmount = blueChannelShiftAmount + blueChannelBitDepth;
        redChannelShiftAmount = greenChannelShiftAmount + greenChannelBitDepth;
    }

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
        float alphaConversionFactor = conversionFactor / 4.f;

        return [=] (unsigned int x, unsigned int y) -> PixelType {
            Coordinate coordinate(x, y);

            auto distanceToTopLeftCorner = coordinate.distanceTo(topLeftCorner);

            float redComponent = std::min(distanceToTopLeftCorner,
                    coordinate.distanceTo(topRightCorner));
            float greenComponent = std::min(distanceToTopLeftCorner,
                    coordinate.distanceTo(bottomLeftCorner));
            float blueComponent = std::min(distanceToTopLeftCorner,
                    coordinate.distanceTo(bottomRightCorner));
            float alphaComponent = distanceToTopLeftCorner;

            redComponent = 1.f - redComponent * conversionFactor;
            greenComponent = 1.f - greenComponent * conversionFactor;
            blueComponent = 1.f - blueComponent * conversionFactor;
            alphaComponent = 1.f - alphaComponent * alphaConversionFactor;

            return makePixelValue(redComponent, greenComponent, blueComponent,
                    alphaComponent);
        };
    }

    PixelType makePixelValue(float redComponent, float greenComponent,
            float blueComponent, float alphaComponent) {
        PixelType pixel = 0;

        redComponent = std::max(1.f, std::abs(redComponent));
        greenComponent = std::max(1.f, std::abs(greenComponent));
        blueComponent = std::max(1.f, std::abs(blueComponent));

        redComponent *= maxRedValue;
        greenComponent *= maxGreenValue;
        blueComponent *= maxBlueValue;

        pixel <<= redChannelBitDepth;
        pixel |= ((PixelType)redComponent) & redChannelMask;

        pixel <<= greenChannelBitDepth;
        pixel |= ((PixelType)greenComponent) & greenChannelMask;

        pixel <<= blueChannelBitDepth;
        pixel |= ((PixelType)blueComponent) & blueChannelMask;

        pixel <<= alphaChannelBitDepth;
        pixel |= ((PixelType)alphaComponent) & alphaChannelMask;

        return pixel;
    }

    PixelType getRedComponentOf(PixelType value) {
        return getColorComponent(value, redChannelShiftAmount, redChannelMask);
    }

    PixelType getGreenComponentOf(PixelType value) {
        return getColorComponent(value, greenChannelShiftAmount,
                greenChannelMask);
    }

    PixelType getBlueComponentOf(PixelType value) {
        return getColorComponent(value, blueChannelShiftAmount,
                blueChannelMask);
    }

    PixelType getAlphaComponentOf(PixelType value) {
        return getColorComponent(value, alphaChannelShiftAmount,
                blueChannelMask);
    }

    PixelType getColorComponent(PixelType value, unsigned int shiftAmount,
            unsigned int mask) {
        return (value >> shiftAmount) & mask;
    }
};

#endif
