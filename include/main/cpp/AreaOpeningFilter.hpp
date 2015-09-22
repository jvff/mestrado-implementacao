#ifndef AREA_OPENING_FILTER_HPP
#define AREA_OPENING_FILTER_HPP

#include "AreaOpeningImplementation.hpp"
#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningFilter : public ComplexFilter<SourceImageType,
        DestinationImageType, AreaOpeningImplementation<SourceImageType,
                DestinationImageType> > {
private:
    using ImplementationType = AreaOpeningImplementation<SourceImageType,
            DestinationImageType>;
    using SuperClass = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    unsigned int maximumPeakSize;

public:
    AreaOpeningFilter(unsigned int maximumPeakSize)
            : maximumPeakSize(maximumPeakSize) {
    }

    ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        return ImplementationType(maximumPeakSize, sourceImage,
                destinationImage);
    }

    using SuperClass::apply;
};

#endif
