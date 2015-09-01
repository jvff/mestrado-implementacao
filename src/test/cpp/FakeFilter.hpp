#ifndef FAKE_FILTER_HPP
#define FAKE_FILTER_HPP

#include <fakeit.hpp>

#include "Filter.hpp"

#include "Unused.hpp"

template <typename SourceImageType, typename DestinationImageType>
class FakeFilter : public Filter<SourceImageType, DestinationImageType> {
private:
    using ParentFilter = Filter<SourceImageType, DestinationImageType>;

public:
    ~FakeFilter() noexcept {
    }

    void apply(const SourceImageType&, DestinationImageType&) override {
    }

    using ParentFilter::createDestinationImage;
    using ParentFilter::getDestinationImageWidth;
    using ParentFilter::getDestinationImageHeight;
};

#endif
