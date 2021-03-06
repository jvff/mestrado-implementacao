#ifndef REGIONAL_MAXIMUMS_FILTER_HPP
#define REGIONAL_MAXIMUMS_FILTER_HPP

#include "Filter.hpp"
#include "MorphologicalReconstructionFilter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class RegionalMaximumsFilter : public Filter<SourceImageType,
        DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;

    using MorphologicalReconstructionFilterType =
            MorphologicalReconstructionFilter<SourceImageType,
                    DestinationImageType>;
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

    MorphologicalReconstructionFilterType subFilter;

public:
    using SuperClass::apply;

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        moveImageDownToCreateMarkerImage(sourceImage, destinationImage);
        removeRegionalMaximums(sourceImage, destinationImage);
        isolateRegionalMaximums(sourceImage, destinationImage);
    }

private:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) {
        return sourceImage.getPixelValue(x, y);
    }

    void moveImageDownToCreateMarkerImage(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        destinationImage = [&] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            return sourceImage.getPixelValue(x, y) - 1;
        };
    }

    void removeRegionalMaximums(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        subFilter.apply(sourceImage, destinationImage);
    }

    void isolateRegionalMaximums(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        destinationImage = [&] (unsigned int x, unsigned int y)
                -> DestinationPixelType{
            auto sourcePixel = sourceImage.getPixelValue(x, y);
            auto destinationPixel = destinationImage.getPixelValue(x, y);
            auto difference = sourcePixel - destinationPixel;

            if (difference == 0)
                return 0;
            else
                return sourcePixel;
        };
    }
};

#endif
