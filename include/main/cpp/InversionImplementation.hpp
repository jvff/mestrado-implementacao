#ifndef INVERSION_IMPLEMENTATION_HPP
#define INVERSION_IMPLEMENTATION_HPP

#include <algorithm>

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class InversionImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

private:
    bool rangeWasNotManuallySet;
    SourcePixelType minimumValue;
    SourcePixelType maximumValue;

    using SuperClass::width;
    using SuperClass::height;
    using SuperClass::sourceImage;
    using SuperClass::destinationImage;

public:
    InversionImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            rangeWasNotManuallySet(true) {
    }

    InversionImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            const SourcePixelType& minimum, const SourcePixelType& maximum)
            : SuperClass(sourceImage, destinationImage),
            rangeWasNotManuallySet(false), minimumValue(minimum),
            maximumValue(maximum) {
    }

    void apply() override {
        discoverRangeIfNecessary();
        invert();
    }

    void discoverRangeIfNecessary() {
        if (rangeWasNotManuallySet)
            discoverRange();
    }

    void discoverRange() {
        initializeRangeValues();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                maybeUpdateRangeValues(sourceImage.getPixelValue(x, y));
        }
    }

    void initializeRangeValues() {
        minimumValue = sourceImage.getPixelValue(0, 0);
        maximumValue = minimumValue;
    }

    void maybeUpdateRangeValues(const SourcePixelType& newValue) {
        minimumValue = std::min(minimumValue, newValue);
        maximumValue = std::max(maximumValue, newValue);
    }

    void invert() {
        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                invertPixel(x, y);
        }
    }

    void invertPixel(unsigned int x, unsigned int y) {
        auto originalValue = sourceImage.getPixelValue(x, y);
        auto invertedValue = maximumValue - originalValue + minimumValue;

        destinationImage.setPixel(x, y, invertedValue);
    }
};

#endif
