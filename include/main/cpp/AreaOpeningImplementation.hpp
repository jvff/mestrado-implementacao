#ifndef AREA_OPENING_IMPLEMENTATION_HPP
#define AREA_OPENING_IMPLEMENTATION_HPP

#include "Image.hpp"

template <typename SourceImageType, typename DestinationImageType>
class AreaOpeningImplementation {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;

    const SourceImageType& sourceImage;
    DestinationImageType& destinationImage;

public:
    AreaOpeningImplementation(unsigned int, const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) : sourceImage(sourceImage),
            destinationImage(destinationImage) {
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
