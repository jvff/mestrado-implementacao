#ifndef AREA_OPENING_IMPLEMENTATION_HPP
#define AREA_OPENING_IMPLEMENTATION_HPP

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AreaOpeningImplementation {
public:
    AreaOpeningImplementation(unsigned int, const SourceImageType&,
            DestinationImageType&) {
    }
};

#endif
