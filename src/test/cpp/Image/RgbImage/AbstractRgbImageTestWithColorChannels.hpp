#ifndef ABSTRACT_RGB_IMAGE_TEST_WITH_COLOR_CHANNELS_HPP
#define ABSTRACT_RGB_IMAGE_TEST_WITH_COLOR_CHANNELS_HPP

#include <memory>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "AbstractRgbImageTestWithInternalImageMock.hpp"
#include "ColorChannel.hpp"
#include "RectangleColorGradientPainter.hpp"

using namespace fakeit;

template <typename PixelType>
class AbstractRgbImageTestWithColorChannels
        : public AbstractRgbImageTestWithInternalImageMock<PixelType> {
protected:
    using SuperClass = AbstractRgbImageTestWithInternalImageMock<PixelType>;
    using InternalImageType = typename SuperClass::InternalImageType;
    using RgbImageType = RgbImage<InternalImageType>;

    std::unique_ptr<RectangleColorGradientPainter<PixelType> > painter;

protected:
    void initializePainter(unsigned int width, unsigned int height,
            bool withAlpha = false) {
        painter.reset(new RectangleColorGradientPainter<PixelType>(width,
                    height, withAlpha));
    }

    Mock<InternalImageType> mockColorInternalImage(unsigned int width,
            unsigned int height) {
        auto& paintFunction = *painter;

        return mockInternalImage(width, height, paintFunction);
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

    void checkRelativeChannelsOfAllPixels(
            const InternalImageType& internalImage,
            const RgbImageType& rgbImage, bool withAlpha) {
        unsigned int width = internalImage.getWidth();
        unsigned int height = internalImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                checkRelativeChannels(x, y, internalImage, rgbImage, withAlpha);
        }
    }

private:
    void checkChannels(unsigned int x, unsigned int y,
            const InternalImageType& internalImage,
            const RgbImageType& rgbImage) {
        PixelType fullValue = internalImage.getPixelValue(x, y);

        auto& redChannel = painter->getRedChannel();
        auto& greenChannel = painter->getGreenChannel();
        auto& blueChannel = painter->getBlueChannel();
        auto& alphaChannel = painter->getAlphaChannel();

        checkChannel(redChannel, fullValue, rgbImage.getRedComponent(x, y));
        checkChannel(greenChannel, fullValue, rgbImage.getGreenComponent(x, y));
        checkChannel(blueChannel, fullValue, rgbImage.getBlueComponent(x, y));
        checkChannel(alphaChannel, fullValue, rgbImage.getAlphaComponent(x, y));
    }

    void checkChannel(const ColorChannel<PixelType>& channel,
            PixelType pixelValue, PixelType channelValue) {
        assertThat(channelValue).isEqualTo(channel.getComponent(pixelValue));
    }

    void checkRelativeChannels(unsigned int x, unsigned int y,
            const InternalImageType& internalImage,
            const RgbImageType& rgbImage, bool withAlpha) {
        PixelType fullValue = internalImage.getPixelValue(x, y);

        auto& redChannel = painter->getRedChannel();
        auto& greenChannel = painter->getGreenChannel();
        auto& blueChannel = painter->getBlueChannel();
        auto& alphaChannel = painter->getAlphaChannel();

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

    void checkRelativeChannel(const ColorChannel<PixelType>& channel,
            PixelType pixelValue, float relativeChannelValue) {
        float expectedValue = channel.getRelativeComponent(pixelValue);

        assertThat(relativeChannelValue).isAlmostEqualTo(expectedValue);
    }

private:
    using SuperClass::mockInternalImage;
};

#endif
