#ifndef LUMINANCE_FILTER_HPP
#define LUMINANCE_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class LuminanceFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

public:
    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        destinationImage = sourceImage;
    }

    using SuperClass::apply;
};

#endif
