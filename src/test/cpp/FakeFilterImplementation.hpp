#ifndef FAKE_FILTER_IMPLEMENTATION_HPP
#define FAKE_FILTER_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class FakeFilterImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

public:
    FakeFilterImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage) {
    }

    const SourceImageType& getSourceImage() {
        return this->sourceImage;
    }

    DestinationImageType& getDestinationImage() {
        return this->destinationImage;
    }

    unsigned int getWidth() {
        return this->width;
    }

    unsigned int getHeight() {
        return this->height;
    }

    void apply() override {
    }
};

#endif
