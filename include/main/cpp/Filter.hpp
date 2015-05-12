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

    virtual void apply(SourceType* sourceImage) {
        getDestinationImageWidth(sourceImage);
        getDestinationImageHeight(sourceImage);
    }
};

#endif
