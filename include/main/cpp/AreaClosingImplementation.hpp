#ifndef AREA_CLOSING_IMPLEMENTATION_HPP
#define AREA_CLOSING_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaClosingImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

public:
    AreaClosingImplementation(unsigned int, const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
    }

    void apply() override {
    }
};

#endif
