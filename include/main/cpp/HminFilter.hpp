#ifndef HMIN_FILTER_HPP
#define HMIN_FILTER_HPP

#include "ComplexFilter.hpp"
#include "HminImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class HminFilter : public ComplexFilter<SourceImageType, DestinationImageType,
        HminImplementation<SourceImageType, DestinationImageType> > {
private:
    using ImplementationType = HminImplementation<SourceImageType,
            DestinationImageType>;
    using SourcePixelType = typename SourceImageType::PixelType;

    SourcePixelType featureHeight;

public:
    HminFilter(const SourcePixelType& featureHeight)
            : featureHeight(featureHeight) {
    }

protected:
    ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        return ImplementationType(featureHeight, sourceImage, destinationImage);
    }
};

#endif
