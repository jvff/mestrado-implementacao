#ifndef AREA_OPENING_IMPLEMENTATION_HPP
#define AREA_OPENING_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"
#include "Image.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    using SuperClass::sourceImage;
    using SuperClass::destinationImage;

public:
    AreaOpeningImplementation(unsigned int, const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    void apply() {
        copySourceImage();
    }

private:
    void copySourceImage() {
        destinationImage = [&] (unsigned int x, unsigned int y)
                -> DestinationPixelType {
            return sourceImage.getPixel(x, y);
        };
    }
};

#endif
