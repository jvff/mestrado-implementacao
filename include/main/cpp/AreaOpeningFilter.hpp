#ifndef AREA_OPENING_FILTER_HPP
#define AREA_OPENING_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AreaOpeningFilter : public Filter<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType> {
private:
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

public:
    AreaOpeningFilter(unsigned int) {
    }

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        destinationImage = sourceImage;
    }

    using SuperClass::apply;
};

#endif
