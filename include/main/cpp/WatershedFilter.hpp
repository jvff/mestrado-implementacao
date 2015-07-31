#ifndef WATERSHED_FILTER_HPP
#define WATERSHED_FILTER_HPP

#include "Filter.hpp"

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

protected:
    DestinationPixelType apply(unsigned int, unsigned int,
            const SourceImageType&) override {
        return 1;
    }
};

#endif
