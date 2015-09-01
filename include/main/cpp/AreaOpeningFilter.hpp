#ifndef AREA_OPENING_FILTER_HPP
#define AREA_OPENING_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningFilter : public Filter<typename SourceImageType::PixelType,
        typename DestinationImageType::PixelType,
        DestinationImageType, SourceImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;
    using DestinationPixelType = typename DestinationImageType::PixelType;

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
