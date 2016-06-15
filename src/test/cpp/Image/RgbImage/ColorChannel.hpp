#ifndef COLOR_CHANNEL_HPP
#define COLOR_CHANNEL_HPP

#include <algorithm>

template <typename PixelType>
class ColorChannel {
private:
    unsigned int bitDepth;
    unsigned int maxValue;
    unsigned int mask;
    unsigned int shiftAmount;

public:
    ColorChannel(unsigned int numberOfChannels, bool shouldUseRemainingBits) {
        unsigned int totalBits = 8 * sizeof(PixelType);

        if (numberOfChannels == 0)
            bitDepth = 0;
        else
            bitDepth = totalBits / numberOfChannels;

        if (shouldUseRemainingBits)
            bitDepth += totalBits - numberOfChannels * bitDepth;

        maxValue = (1 << bitDepth) - 1;
        mask = maxValue;
        shiftAmount = 0;
    }

    void isAfter(const ColorChannel& channel) {
        shiftAmount = channel.shiftAmount + channel.bitDepth;
    }

    PixelType getComponent(PixelType pixelValue) const {
        return (pixelValue >> shiftAmount) & mask;
    }

    float getRelativeComponent(PixelType pixelValue) const {
        float component = getComponent(pixelValue);

        return component / (float)maxValue;
    }

    void apply(float relativeComponent, PixelType& pixel) const {
        PixelType component = std::min(1.f, relativeComponent) * maxValue;

        apply(component, pixel);
    }

    void apply(PixelType component, PixelType& pixel) const {
        PixelType shiftedComponent = (component & mask) << shiftAmount;

        pixel &= mask << shiftAmount;
        pixel |= shiftedComponent;
    }
};

#endif
