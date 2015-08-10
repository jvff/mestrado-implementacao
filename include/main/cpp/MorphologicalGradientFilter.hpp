#ifndef MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class MorphologicalGradientFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
public:
    MorphologicalGradientFilter(unsigned int structureSize) {
    }

protected:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
    }
};

#endif
