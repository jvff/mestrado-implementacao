#ifndef AREA_CLOSING_FILTER_HPP
#define AREA_CLOSING_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AreaClosingFilter : public Filter<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType> {
};

#endif
