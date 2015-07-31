#ifndef WATERSHED_FILTER_HPP
#define WATERSHED_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class WatershedFilter : public Filter<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType> {
protected:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        return sourceImage.getPixel(x, y);
    }
};

#endif
