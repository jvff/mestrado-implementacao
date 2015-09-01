#ifndef AREA_CLOSING_FILTER_HPP
#define AREA_CLOSING_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaClosingFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

public:
    AreaClosingFilter(unsigned int) {
    }

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        destinationImage = sourceImage;
    }

    using SuperClass::apply;
};

#endif
