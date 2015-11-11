#ifndef HMIN_IMPLEMENTATION_HPP
#define HMIN_IMPLEMENTATION_HPP

#include <algorithm>

#include "FilterImplementation.hpp"
#include "HmaxFilter.hpp"
#include "InversionImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class HminImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using InversionImplementationType = InversionImplementation<SourceImageType,
            DestinationImageType>;
    using SourcePixelType = typename SourceImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    SourcePixelType featureHeight;

    DestinationPixelType minimumPixelValue;
    DestinationPixelType maximumPixelValue;
    DestinationImageType invertedSourceImage;
    DestinationImageType invertedDestinationImage;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;

public:
    HminImplementation(const SourcePixelType& featureHeight,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            featureHeight(featureHeight), invertedSourceImage(width, height),
            invertedDestinationImage(width, height) {
    }

    void apply() override {
        findInversionRange();
        invertSourceImage();
        applyHmaxFilter();
        invertDestinationImage();
    }

private:
    void findInversionRange() {
        minimumPixelValue = sourceImage.getPixelValue(0, 0);
        maximumPixelValue = minimumPixelValue;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                DestinationPixelType pixelValue =
                        sourceImage.getPixelValue(x, y);

                minimumPixelValue = std::min(minimumPixelValue, pixelValue);
                maximumPixelValue = std::max(maximumPixelValue, pixelValue);
            }
        }
    }

    void invertSourceImage() {
        InversionImplementationType(sourceImage, invertedSourceImage,
                minimumPixelValue, maximumPixelValue).apply();
    }

    void applyHmaxFilter() {
        HmaxFilter<SourceImageType, DestinationImageType> filter(featureHeight);

        filter.apply(invertedSourceImage, invertedDestinationImage);
    }

    void invertDestinationImage() {
        InversionImplementationType(invertedDestinationImage, destinationImage,
                minimumPixelValue, maximumPixelValue).apply();
    }
};

#endif
