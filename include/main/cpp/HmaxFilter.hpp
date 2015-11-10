#ifndef HMAX_FILTER_HPP
#define HMAX_FILTER_HPP

#include "MorphologicalReconstructionFilter.hpp"
#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class HmaxFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using MorphologicalReconstructionFilterType =
            MorphologicalReconstructionFilter<SourceImageType, DestinationImageType>;
    using SourcePixelType = typename SourceImageType::PixelType;
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

    MorphologicalReconstructionFilterType morphologicalReconstructionFilter;
    SourcePixelType featureHeight;

public:
    HmaxFilter(const SourcePixelType& featureHeight)
            : featureHeight(featureHeight) {
    }

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        setUpMarkerImage(sourceImage, destinationImage);

        morphologicalReconstructionFilter.apply(sourceImage, destinationImage);
    }

    using SuperClass::apply;

private:
    void setUpMarkerImage(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        destinationImage = [&] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            return sourceImage.getPixelValue(x, y) - featureHeight;
        };
    }
};

#endif
