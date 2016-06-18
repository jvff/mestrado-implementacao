#ifndef LUMINANCE_FILTER_HPP
#define LUMINANCE_FILTER_HPP

#include <cmath>

#include "Filter.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"
#include "RgbImage.hpp"
#include "SimpleFilter.hpp"

#include "cl/BypassFilter.h"

template <typename SourceImageType, typename DestinationImageType>
class LuminanceFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

public:
    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        destinationImage.paint(sourceImage);
    }

    using SuperClass::apply;
};

template <typename InternalImageType, typename DestinationImageType>
class LuminanceFilter<RgbImage<InternalImageType>, DestinationImageType>
        : public SimpleFilter<RgbImage<InternalImageType>,
                DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using SourceImageType = RgbImage<InternalImageType>;
    using SuperClass = SimpleFilter<SourceImageType, DestinationImageType>;

public:
    using SuperClass::apply;

protected:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) {
        float redComponent = sourceImage.getRelativeRedComponent(x, y);
        float greenComponent = sourceImage.getRelativeGreenComponent(x, y);
        float blueComponent = sourceImage.getRelativeBlueComponent(x, y);

        float redContribution = 0.2126 * redComponent;
        float greenContribution = 0.7152 * greenComponent;
        float blueContribution = 0.0722 * blueComponent;

        float luminance = 0.f;
        float conversionFactor = getMaximumLuminanceValue();

        luminance += redContribution;
        luminance += greenContribution;
        luminance += blueContribution;

        return (DestinationPixelType)std::round(luminance * conversionFactor);
    }

    float getMaximumLuminanceValue() {
        return std::numeric_limits<DestinationPixelType>::max();
    }
};

template <typename PixelType>
class LuminanceFilter<OpenCLImage<PixelType>, OpenCLImage<PixelType> >
        : public OpenCLFilter<PixelType> {
private:
    using SuperClass = OpenCLFilter<PixelType>;

public:
    LuminanceFilter() : SuperClass(BypassFilterSourceCode, "copyImage") {
    }
};

#endif
