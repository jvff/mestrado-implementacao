#ifndef WATERSHED_FILTER_HPP
#define WATERSHED_FILTER_HPP

#include "ComplexFilter.hpp"
#include "WatershedImplementation.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class WatershedFilter : public ComplexFilter<SourceImageType,
        DestinationImageType, WatershedImplementation<SourceImageType,
                DestinationImageType> > {
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
