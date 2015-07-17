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
public:
    ~FakeFilter() noexcept {
    }

    unsigned int getDestinationImageWidth(const SourceImageType& sourceImage) {
        unused(sourceImage);

        return 0;
    }

    unsigned int getDestinationImageHeight(const SourceImageType& sourceImage) {
        unused(sourceImage);

        return 0;
    }

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        Filter<SourcePixelType, DestinationPixelType, DestinationImageType,
                SourceImageType>::apply(sourceImage, destinationImage);
    }

    DestinationPixelType apply(unsigned int x, unsigned int y,
            const SourceImageType& sourceImage) {
        unused(x, y, sourceImage);

        DestinationPixelType defaultValue;

        return defaultValue;
    }

    using Filter<SourcePixelType, DestinationPixelType, DestinationImageType,
            SourceImageType>::createDestinationImage;
};

#endif
