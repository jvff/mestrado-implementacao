#ifndef WATERSHED_FILTER_HPP
#define WATERSHED_FILTER_HPP

#include "Filter.hpp"
#include "WatershedImplementation.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class WatershedFilter : public Filter<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType> {
private:
    using ParentFilter = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

public:
    using ParentFilter::apply;

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        using Implementation = WatershedImplementation<SourceImageType,
                DestinationImageType>;

        Implementation(sourceImage, destinationImage).apply();
    }

protected:
    DestinationImageType createDestinationImage(unsigned int width,
            unsigned int height) override {
        auto image = ParentFilter::createDestinationImage(width, height);

        image = [] (unsigned int, unsigned int) -> DestinationPixelType {
            return 0;
        };

        return image;
    }
};

#endif
