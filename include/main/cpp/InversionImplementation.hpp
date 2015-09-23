#ifndef INVERSION_IMPLEMENTATION_HPP
#define INVERSION_IMPLEMENTATION_HPP

#include "FilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType>
class InversionImplementation
        : public FilterImplementation<SourceImageType, DestinationImageType> {
private:
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

public:
    using SuperClass::FilterImplementation;

    void apply() override {
    }
};

#endif
