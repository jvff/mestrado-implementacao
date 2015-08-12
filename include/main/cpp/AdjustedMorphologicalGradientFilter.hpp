#ifndef ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AdjustedMorphologicalGradientFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
public:
    AdjustedMorphologicalGradientFilter(unsigned int, const SourcePixelType&,
            const DestinationPixelType&, float)
    }

private:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return sourceImage.getPixel(x, y);
    }
};

#endif
