#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include <type_traits>

#include "Image.hpp"

template <typename InternalImageType>
class RgbImage : public Image<typename InternalImageType::PixelType> {
private:
    using PixelType = typename InternalImageType::PixelType;
    using SuperClass = Image<PixelType>;

    static constexpr bool pixelTypeIsSupported() {
        return std::is_integral<PixelType>::value
            && !std::is_same<PixelType, bool>::value;
    }

    static_assert(pixelTypeIsSupported(), "Unsupported pixel type");

private:
    InternalImageType& internalImage;

    unsigned int redChannelShiftAmount;
    unsigned int greenChannelShiftAmount;
    unsigned int blueChannelShiftAmount;
    unsigned int alphaChannelShiftAmount;

    unsigned int redChannelMask;
    unsigned int greenChannelMask;
    unsigned int blueChannelMask;
    unsigned int alphaChannelMask;

public:
    RgbImage(InternalImageType& internalImage, bool hasAlpha = false)
            : SuperClass(internalImage.getWidth(), internalImage.getHeight()),
            internalImage(internalImage) {
        unsigned int availableBits = 8 * sizeof(PixelType);
        unsigned int numberOfChannels = hasAlpha ? 4 : 3;

        auto bitsPerChannel = availableBits / numberOfChannels;
        auto remainingBits = availableBits - numberOfChannels * bitsPerChannel;

        auto redChannelBits = bitsPerChannel;
        auto greenChannelBits = bitsPerChannel + remainingBits;
        auto blueChannelBits = bitsPerChannel;
        auto alphaChannelBits = hasAlpha ? bitsPerChannel : 0;

        alphaChannelShiftAmount = 0;
        blueChannelShiftAmount = alphaChannelShiftAmount + alphaChannelBits;
        greenChannelShiftAmount = blueChannelShiftAmount + blueChannelBits;
        redChannelShiftAmount = greenChannelShiftAmount + greenChannelBits;

        redChannelMask = (1 << redChannelBits) - 1;
        greenChannelMask = (1 << greenChannelBits) - 1;
        blueChannelMask = (1 << blueChannelBits) - 1;
        alphaChannelMask = (1 << alphaChannelBits) - 1;
    }

    void setPixel(unsigned int x, unsigned int y, PixelType value) override {
        internalImage.setPixel(x, y, value);
    }

    PixelType getPixelValue(unsigned int x, unsigned int y) const override {
        return internalImage.getPixelValue(x, y);
    }

    virtual PixelType getRedComponent(unsigned int x, unsigned int y) const {
        return getColorComponent(x, y, redChannelShiftAmount, redChannelMask);
    }

    virtual PixelType getGreenComponent(unsigned int x, unsigned int y) const {
        return getColorComponent(x, y, greenChannelShiftAmount,
                greenChannelMask);
    }

    virtual PixelType getBlueComponent(unsigned int x, unsigned int y) const {
        return getColorComponent(x, y, blueChannelShiftAmount, blueChannelMask);
    }

    virtual PixelType getAlphaComponent(unsigned int x, unsigned int y) const {
        return getColorComponent(x, y, alphaChannelShiftAmount,
                alphaChannelMask);
    }

    using SuperClass::operator=;

private:
    PixelType getColorComponent(unsigned int x, unsigned int y,
            unsigned int channelShiftAmount, PixelType channelMask) const {
        PixelType value = internalImage.getPixelValue(x, y);

        return (value >> channelShiftAmount) & channelMask;
    }
};

#endif
