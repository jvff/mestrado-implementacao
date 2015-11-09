#ifndef AREA_CLOSING_FILTER_HPP
#define AREA_CLOSING_FILTER_HPP

#include "AreaClosingImplementation.hpp"
#include "ComplexFilter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaClosingFilter : public ComplexFilter<SourceImageType,
        DestinationImageType, AreaClosingImplementation<SourceImageType,
                DestinationImageType> > {
private:
    using ImplementationType = AreaClosingImplementation<SourceImageType,
            DestinationImageType>;
    using SuperClass = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    unsigned int maximumHoleSize;

public:
    AreaClosingFilter(unsigned int maximumHoleSize)
            : maximumHoleSize(maximumHoleSize) {
    }

    ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        return ImplementationType(maximumHoleSize, sourceImage,
                destinationImage);
    }

    using SuperClass::apply;
};

#endif
