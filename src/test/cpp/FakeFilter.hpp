#ifndef FAKE_FILTER_HPP
#define FAKE_FILTER_HPP

#include <fakeit.hpp>

#include "Filter.hpp"

template <typename SourceType, typename DestinationType>
class FakeFilter : public Filter<SourceType, DestinationType> {
private:
    ImageFactory<DestinationType>* originalImageFactory;
    fakeit::Mock<ImageFactory<DestinationType> > mockImageFactory;

public:
    FakeFilter() {
        originalImageFactory = this->imageFactory;
        this->imageFactory = &mockImageFactory.get();
    }

    ~FakeFilter() noexcept {
        this->imageFactory = originalImageFactory;
    }

    ImageFactory<DestinationType>* getImageFactory() {
        return originalImageFactory;
    }

    fakeit::Mock<ImageFactory<DestinationType> >& getImageFactoryMock() {
        return mockImageFactory;
    }

    int getDestinationImageWidth(SourceType* sourceImage) {
        return 0;
    }

    int getDestinationImageHeight(SourceType* sourceImage) {
        return 0;
    }
};

#endif
