#ifndef HMIN_IMPLEMENTATION_HPP
#define HMIN_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class HminImplementation : public FilterImplementation<SourceImageType,
        DestinationImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;

public:
    HminImplementation(const SourcePixelType&, const SourceImageType&,
            DestinationImageType&) {
    }

    void apply() override {
    }
};

#endif
