#ifndef AREA_CLOSING_IMPLEMENTATION_HPP
#define AREA_CLOSING_IMPLEMENTATION_HPP

#include "AreaOpeningImplementation.hpp"
#include "FilterImplementation.hpp"
#include "InversionImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaClosingImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;
    using SuperClass::width;
    using SuperClass::height;

    DestinationImageType invertedSourceImage;
    unsigned int maximumHoleSize;

    SourcePixelType minPixelValue;
    SourcePixelType maxPixelValue;

public:
    AreaClosingImplementation(unsigned int maximumHoleSize,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
            invertedSourceImage(width, height),
            maximumHoleSize(maximumHoleSize) {
    }

    void apply() override {
        getPixelValueRange();
        invertSourceImage();
        openAreas();
        invertDestinationImage();
    }

private:
    void getPixelValueRange() {
        minPixelValue = sourceImage.getPixelValue(0, 0);
        maxPixelValue = minPixelValue;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                SourcePixelType pixelValue = sourceImage.getPixelValue(x, y);

                if (pixelValue < minPixelValue)
                    minPixelValue = pixelValue;

                if (pixelValue > maxPixelValue)
                    maxPixelValue = pixelValue;
            }
        }
    }

    void invertSourceImage() {
        InversionImplementation<SourceImageType, SourceImageType>(sourceImage,
                invertedSourceImage, minPixelValue, maxPixelValue).apply();
    }

    void openAreas() {
        AreaOpeningImplementation<SourceImageType, DestinationImageType>(
                maximumHoleSize, invertedSourceImage, destinationImage).apply();
    }

    void invertDestinationImage() {
        InversionImplementation<DestinationImageType, DestinationImageType>(
                destinationImage, destinationImage, minPixelValue,
                maxPixelValue).apply();
    }
};

#endif
