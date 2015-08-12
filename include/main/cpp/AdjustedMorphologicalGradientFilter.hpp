#ifndef ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define ADJUSTED_MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AdjustedMorphologicalGradientFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
};

#endif
