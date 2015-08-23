#ifndef FILTER_HPP
#define FILTER_HPP

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class Filter {
public:
    virtual ~Filter() {
    }

    virtual DestinationImageType apply(const SourceImageType& sourceImage) {
        unsigned int width = getDestinationImageWidth(sourceImage);
        unsigned int height = getDestinationImageHeight(sourceImage);
        auto destinationImage = createDestinationImage(width, height);

        apply(sourceImage, destinationImage);

        return destinationImage;
    }

    virtual void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) = 0;

protected:
    virtual unsigned int getDestinationImageWidth(
            const SourceImageType& sourceImage) {
        return sourceImage.getWidth();
    }

    virtual unsigned int getDestinationImageHeight(
            const SourceImageType& sourceImage) {
        return sourceImage.getHeight();
    }

    virtual DestinationImageType createDestinationImage(unsigned int width,
            unsigned int height) {
        return DestinationImageType(width, height);
    }
};

#endif
