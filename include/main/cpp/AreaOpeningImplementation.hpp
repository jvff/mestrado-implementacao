#ifndef AREA_OPENING_IMPLEMENTATION_HPP
#define AREA_OPENING_IMPLEMENTATION_HPP

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        typename DestinationImageType,
        typename SourceImageType = Image<SourcePixelType> >
class AreaOpeningImplementation {
private:
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
