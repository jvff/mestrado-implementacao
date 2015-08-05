#ifndef WATERSHED_IMPLEMENTATION_HPP
#define WATERSHED_IMPLEMENTATION_HPP

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class WatershedImplementation {
public:
    WatershedImplementation(const SourceImageType&, DestinationImageType&) {
    }
};

#endif
