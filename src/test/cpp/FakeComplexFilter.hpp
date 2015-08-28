#ifndef FAKE_COMPLEX_FILTER_HPP
#define FAKE_COMPLEX_FILTER_HPP

#include "ComplexFilter.hpp"

template <typename SourceImageType, typename DestinationImageType,
        typename ImplementationType>
class FakeComplexFilter : public ComplexFilter<SourceImageType,
        DestinationImageType, ImplementationType> {
private:
    using SuperClass = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

public:
    using SuperClass::instantiateImplementation;
};

#endif
