#ifndef AREA_OPENING_FILTER_HPP
#define AREA_OPENING_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

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
