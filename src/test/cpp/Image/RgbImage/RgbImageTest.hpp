#ifndef RGB_IMAGE_TEST_HPP
#define RGB_IMAGE_TEST_HPP

#include <cmath>
#include <cstdint>
#include <memory>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "ColorChannel.hpp"

#include "../../FakeImage.hpp"

using namespace fakeit;

template <typename PixelTypeParameter>
class RgbImageTest : public ::testing::Test {
protected:
    using PixelType = PixelTypeParameter;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageType = RgbImage<InternalImageType>;
    using PaintFunction = std::function<PixelType(unsigned int, unsigned int)>;

    std::unique_ptr<ColorChannel<PixelType> > redChannel;
    std::unique_ptr<ColorChannel<PixelType> > greenChannel;
    std::unique_ptr<ColorChannel<PixelType> > blueChannel;
    std::unique_ptr<ColorChannel<PixelType> > alphaChannel;

protected:
    void calculateChannelParameters(bool withAlpha = false) {
        unsigned int numChannels = withAlpha ? 4 : 3;

        redChannel.reset(new ColorChannel<PixelType>(numChannels, false));
        greenChannel.reset(new ColorChannel<PixelType>(numChannels, true));
        blueChannel.reset(new ColorChannel<PixelType>(numChannels, false));

        if (withAlpha) {
            alphaChannel.reset(new ColorChannel<PixelType>(numChannels, false));
            blueChannel->isAfter(*alphaChannel);
        } else
            alphaChannel.reset(new ColorChannel<PixelType>(0, false));

        greenChannel->isAfter(*blueChannel);
        redChannel->isAfter(*greenChannel);
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

        redChannel->apply(std::abs(redComponent), pixel);
        greenChannel->apply(std::abs(greenComponent), pixel);
        blueChannel->apply(std::abs(blueComponent), pixel);
        alphaChannel->apply(std::abs(alphaComponent), pixel);

        return pixel;
    }

    void checkChannelsOfAllPixels(const InternalImageType& internalImage,
            const RgbImageType& rgbImage) {
        unsigned int width = internalImage.getWidth();
        unsigned int height = internalImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                checkChannels(x, y, internalImage, rgbImage);
        }
    }

    void checkChannels(unsigned int x, unsigned int y,
            const InternalImageType& internalImage,
            const RgbImageType& rgbImage) {
        PixelType fullValue = internalImage.getPixelValue(x, y);

        checkChannel(redChannel, fullValue, rgbImage.getRedComponent(x, y));
        checkChannel(greenChannel, fullValue, rgbImage.getGreenComponent(x, y));
        checkChannel(blueChannel, fullValue, rgbImage.getBlueComponent(x, y));
        checkChannel(alphaChannel, fullValue, rgbImage.getAlphaComponent(x, y));
    }

    void checkChannel(std::unique_ptr<ColorChannel<PixelType> >& channel,
            PixelType pixelValue, PixelType channelValue) {
        assertThat(channelValue).isEqualTo(channel->getComponent(pixelValue));
    }

    void checkRelativeChannelsOfAllPixels(const InternalImageType& internalImage,
            const RgbImageType& rgbImage, bool withAlpha) {
        unsigned int width = internalImage.getWidth();
        unsigned int height = internalImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                checkRelativeChannels(x, y, internalImage, rgbImage, withAlpha);
        }
    }

    void checkRelativeChannels(unsigned int x, unsigned int y,
            const InternalImageType& internalImage,
            const RgbImageType& rgbImage, bool withAlpha) {
        PixelType fullValue = internalImage.getPixelValue(x, y);

        checkRelativeChannel(redChannel, fullValue,
                rgbImage.getRelativeRedComponent(x, y));

        checkRelativeChannel(greenChannel, fullValue,
                rgbImage.getRelativeGreenComponent(x, y));

        checkRelativeChannel(blueChannel, fullValue,
                rgbImage.getRelativeBlueComponent(x, y));

        if (withAlpha) {
            checkRelativeChannel(alphaChannel, fullValue,
                    rgbImage.getRelativeAlphaComponent(x, y));
        }
    }

    void checkRelativeChannel(
            std::unique_ptr<ColorChannel<PixelType> >& channel,
            PixelType pixelValue, float relativeChannelValue) {
        float expectedValue = channel->getRelativeComponent(pixelValue);

        assertThat(relativeChannelValue).isAlmostEqualTo(expectedValue);
    }
};

#endif
