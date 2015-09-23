#ifndef INVERSION_IMPLEMENTATION_HPP
#define INVERSION_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class InversionImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

private:
    using SuperClass::sourceImage;
    using SuperClass::destinationImage;

public:
    using SuperClass::FilterImplementation;

    InversionImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage, const SourcePixelType&,
            const SourcePixelType&)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() override {
        destinationImage = sourceImage;
    }
};

#endif
