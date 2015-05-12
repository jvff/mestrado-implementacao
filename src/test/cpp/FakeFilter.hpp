#ifndef FAKE_FILTER_HPP
#define FAKE_FILTER_HPP

#include <fakeit.hpp>

#include "Filter.hpp"

#include "MockInterceptor.hpp"

template <typename SourceType, typename DestinationType>
class FakeFilter : public Filter<SourceType, DestinationType> {
private:
    MockInterceptor<ImageFactory<DestinationType> > imageFactoryHandler;

public:
    FakeFilter() : imageFactoryHandler(this->imageFactory) {
    }

    ~FakeFilter() noexcept {
    }

    ImageFactory<DestinationType>* getImageFactory() {
        return imageFactoryHandler.getOriginal();
    }

    fakeit::Mock<ImageFactory<DestinationType> >& getImageFactoryMock() {
        return imageFactoryHandler.getMock();
    }

    int getDestinationImageWidth(SourceType* sourceImage) {
        return 0;
    }

    int getDestinationImageHeight(SourceType* sourceImage) {
        return 0;
    }
};

#endif
