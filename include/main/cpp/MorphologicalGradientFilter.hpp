#ifndef MORPHOLOGICAL_GRADIENT_FILTER_HPP
#define MORPHOLOGICAL_GRADIENT_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class MorphologicalGradientFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
};

#endif
