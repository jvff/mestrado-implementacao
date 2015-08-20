#ifndef FAKE_SIMPLE_FILTER_HPP
#define FAKE_SIMPLE_FILTER_HPP

#include "SimpleFilter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class FakeSimpleFilter : public SimpleFilter<SourceImageType,
        DestinationImageType> {
private:
    using DestinationPixelType = typename DestinationImageType::PixelType;
    using SuperClass = SimpleFilter<SourceImageType, DestinationImageType>;

public:
    using SuperClass::apply;

protected:
    DestinationPixelType apply(unsigned int, unsigned int,
            const SourceImageType&) {
        return DestinationPixelType();
    }
};

#endif
