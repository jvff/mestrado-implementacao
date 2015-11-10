#ifndef HMAX_FILTER_HPP
#define HMAX_FILTER_HPP

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class HmaxFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using SourcePixelType = typename SourceImageType::PixelType;

public:
    HmaxFilter(const SourcePixelType&) {
    }

    void apply(const SourceImageType&, DestinationImageType&) override {
    }
};

#endif
