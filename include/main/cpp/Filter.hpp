#ifndef FILTER_HPP
#define FILTER_HPP

#include "ImageFactory.hpp"

template <typename SourceType, typename DestinationType>
class Filter {
protected:
    ImageFactory<DestinationType>* imageFactory;

    virtual int getDestinationImageWidth(SourceType* sourceImage) = 0;
    virtual int getDestinationImageHeight(SourceType* sourceImage) = 0;

public:
    Filter() {
        imageFactory = new ImageFactory<DestinationType>();
    }

    virtual ~Filter() {
        delete imageFactory;
    }

    virtual DestinationType* apply(SourceType* sourceImage) {
        int width = getDestinationImageWidth(sourceImage);
        int height = getDestinationImageHeight(sourceImage);

        return imageFactory->createImage(width, height);
    }
};

#endif
