#ifndef SIMPLE_FILTER_HPP
#define SIMPLE_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class SimpleFilter : public Filter<typename SourceImageType::PixelType,
        typename DestinationImageType::PixelType, DestinationImageType,
        SourceImageType> {
};

#endif
