#ifndef FAKE_FILTER_HPP
#define FAKE_FILTER_HPP

#include "Filter.hpp"


template <typename SourceType, typename DestinationType>
class FakeFilter : public Filter<SourceType, DestinationType> {
public:
    ImageFactory<DestinationType>* getImageFactory() {
        return this->imageFactory;
    }

    int getDestinationImageWidth(SourceType* sourceImage) {
        return 0;
    }

    int getDestinationImageHeight(SourceType* sourceImage) {
        return 0;
    }
};

#endif
