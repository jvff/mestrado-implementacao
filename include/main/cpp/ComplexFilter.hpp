#ifndef COMPLEX_FILTER_HPP
#define COMPLEX_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType,
        typename ImplementationType>
class ComplexFilter : public Filter<typename SourceImageType::PixelType,
        typename DestinationImageType::PixelType, DestinationImageType,
        SourceImageType> {
public:
    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        instantiateImplementation(sourceImage, destinationImage).apply();
    }

protected:
    virtual ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        return ImplementationType(sourceImage, destinationImage);
    }
};

#endif
