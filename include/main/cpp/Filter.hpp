#ifndef FILTER_HPP
#define FILTER_HPP

#include "ImageFactory.hpp"

template <typename SourceType, typename DestinationType>
class Filter {
protected:
    ImageFactory<DestinationType>* imageFactory;

public:
    Filter() {
        imageFactory = new ImageFactory<DestinationType>();
    }

    virtual ~Filter() {
        delete imageFactory;
    }
};

#endif
