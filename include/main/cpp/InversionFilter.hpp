#ifndef INVERSION_FILTER_HPP
#define INVERSION_FILTER_HPP

#include "ComplexFilter.hpp"
#include "InversionImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class InversionFilter
        : public ComplexFilter<SourceImageType, DestinationImageType,
                InversionImplementation<SourceImageType,
                        DestinationImageType> > {
private:
    using ImplementationType = InversionImplementation<SourceImageType,
            DestinationImageType>;
    using SourcePixelType = typename SourceImageType::PixelType;

    bool wasManuallyConfigured;
    SourcePixelType minimumValue;
    SourcePixelType maximumValue;

public:
    InversionFilter() : wasManuallyConfigured(false) {
    }

    InversionFilter(const SourcePixelType& minimumValue,
            const SourcePixelType& maximumValue) : wasManuallyConfigured(true),
            minimumValue(minimumValue), maximumValue(maximumValue) {
    }

    ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        if (wasManuallyConfigured) {
            return ImplementationType(sourceImage, destinationImage,
                    minimumValue, maximumValue);
        } else
            return ImplementationType(sourceImage, destinationImage);
    }
};

#endif
