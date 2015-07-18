#ifndef FILTER_HPP
#define FILTER_HPP

#include "Image.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class Filter {
protected:
    virtual unsigned int getDestinationImageWidth(
            const SourceImageType& sourceImage) = 0;
    virtual unsigned int getDestinationImageHeight(
            const SourceImageType& sourceImage) = 0;
    virtual DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) = 0;

    virtual DestinationImageType createDestinationImage(unsigned int width,
            unsigned int height) {
        return DestinationImageType(width, height);
    }

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
            DestinationImageType& destinationImage) {
        unsigned int width = destinationImage.getWidth();
        unsigned int height = destinationImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                auto newPixel = apply(x, y, sourceImage);

                destinationImage.setPixel(x, y, newPixel);
            }
        }
    }
};

#endif
