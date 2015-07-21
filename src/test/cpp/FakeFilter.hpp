#ifndef FAKE_FILTER_HPP
#define FAKE_FILTER_HPP

#include <fakeit.hpp>

#include "Filter.hpp"

#include "Unused.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class FakeFilter : public Filter<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType> {
private:
    using ParentFilter = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;
public:
    ~FakeFilter() noexcept {
    }

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        ParentFilter::apply(sourceImage, destinationImage);
    }

    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) override {
        unused(x, y, sourceImage);

        DestinationPixelType defaultValue;

        return defaultValue;
    }

    using ParentFilter::createDestinationImage;
    using ParentFilter::getDestinationImageWidth;
    using ParentFilter::getDestinationImageHeight;
};

#endif
