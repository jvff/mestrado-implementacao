#ifndef ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include "Filter.hpp"
#include "MorphologicalGradientFilter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AdjustedMorphologicalGradientFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
private:
    using MorphologicalGradientFilterType = MorphologicalGradientFilter<
            SourcePixelType, DestinationPixelType, DestinationImageType,
            SourceImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    MorphologicalGradientFilterType unadjustedFilter;

public:
    AdjustedMorphologicalGradientFilter(unsigned int structureSize,
            const SourcePixelType&, const DestinationPixelType&, float)
            : unadjustedFilter(structureSize) {
    }

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        unadjustedFilter.apply(sourceImage, destinationImage);
    }

    using SuperClass::apply;

private:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return sourceImage.getPixel(x, y);
    }
};

#endif
