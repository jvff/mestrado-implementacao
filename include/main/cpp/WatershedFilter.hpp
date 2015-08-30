#ifndef WATERSHED_FILTER_HPP
#define WATERSHED_FILTER_HPP

#include "ComplexFilter.hpp"
#include "WatershedImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class WatershedFilter : public ComplexFilter<SourceImageType,
        DestinationImageType, WatershedImplementation<SourceImageType,
                DestinationImageType> > {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            WatershedImplementation<SourceImageType, DestinationImageType> >;

public:
    using ParentFilter::apply;

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
