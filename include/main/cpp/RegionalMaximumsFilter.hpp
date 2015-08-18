#ifndef REGIONAL_MAXIMUMS_FILTER_HPP
#define REGIONAL_MAXIMUMS_FILTER_HPP

#include "Filter.hpp"
#include "MorphologicalReconstructionFilter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class RegionalMaximumsFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
private:
    using MorphologicalReconstructionFilterType =
            MorphologicalReconstructionFilter<SourcePixelType,
                    DestinationImageType, SourceImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

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
        return sourceImage.getPixel(x, y);
    }

    void moveImageDownToCreateMarkerImage(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        destinationImage = [&] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            return sourceImage.getPixel(x, y) - 1;
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
            auto sourcePixel = sourceImage.getPixel(x, y);
            auto destinationPixel = destinationImage.getPixel(x, y);
            auto difference = sourcePixel - destinationPixel;

            if (difference == 0)
                return 0;
            else
                return sourcePixel;
        };
    }
};

#endif
