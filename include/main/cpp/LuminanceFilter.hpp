#ifndef LUMINANCE_FILTER_HPP
#define LUMINANCE_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class LuminanceFilter : public Filter<SourceImageType, DestinationImageType> {
};

#endif
