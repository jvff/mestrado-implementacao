#ifndef FILTER_HPP
#define FILTER_HPP

#include "Image.hpp"
#include "ImageFactory.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class Filter {
protected:
    ImageFactory<DestinationImageType>* imageFactory;

    virtual int getDestinationImageWidth(SourceImageType* sourceImage) = 0;
    virtual int getDestinationImageHeight(SourceImageType* sourceImage) = 0;

public:
    Filter() {
        imageFactory = new ImageFactory<DestinationImageType>();
    }

    virtual ~Filter() {
        delete imageFactory;
    }

    virtual DestinationImageType* apply(SourceImageType* sourceImage) {
        int width = getDestinationImageWidth(sourceImage);
        int height = getDestinationImageHeight(sourceImage);

        return imageFactory->createImage(width, height);
    }
};

#endif
