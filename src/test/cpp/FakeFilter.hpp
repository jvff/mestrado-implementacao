#ifndef FAKE_FILTER_HPP
#define FAKE_FILTER_HPP

#include <fakeit.hpp>

#include "Filter.hpp"

#include "MockInterceptor.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class FakeFilter : public Filter<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType> {
private:
    MockInterceptor<ImageFactory<DestinationImageType> > imageFactoryHandler;

public:
    FakeFilter() : imageFactoryHandler(this->imageFactory) {
    }

    ~FakeFilter() noexcept {
    }

    ImageFactory<DestinationImageType>* getImageFactory() {
        return imageFactoryHandler.getOriginal();
    }

    fakeit::Mock<ImageFactory<DestinationImageType> >& getImageFactoryMock() {
        return imageFactoryHandler.getMock();
    }

    int getDestinationImageWidth(SourceImageType* sourceImage) {
        return 0;
    }

    int getDestinationImageHeight(SourceImageType* sourceImage) {
        return 0;
    }
};

#endif
