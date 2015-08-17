#ifndef REGIONAL_MAXIMUMS_FILTER_HPP
#define REGIONAL_MAXIMUMS_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class RegionalMaximumsFilter : public Filter<SourcePixelType,
        DestinationPixelType, DestinationImageType, SourceImageType> {
private:
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

public:
    using SuperClass::apply;

private:
    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) {
        return sourceImage.getPixel(x, y);
    }
};

#endif
