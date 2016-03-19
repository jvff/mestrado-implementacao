#ifndef FAKE_ABSTRACT_FILTER_HPP
#define FAKE_ABSTRACT_FILTER_HPP

#include <fakeit.hpp>

#include "AbstractFilter.hpp"

template <typename SourceImageType, typename DestinationImageType>
class FakeAbstractFilter
        : public AbstractFilter<SourceImageType, DestinationImageType> {
private:
    using SuperClass = AbstractFilter<SourceImageType, DestinationImageType>;

public:
    ~FakeAbstractFilter() noexcept {
    }

    DestinationImageType createDestinationImage(const SourceImageType&)
            override {
        return DestinationImageType(1, 1);
    }

    using SuperClass::apply;
};

#endif
