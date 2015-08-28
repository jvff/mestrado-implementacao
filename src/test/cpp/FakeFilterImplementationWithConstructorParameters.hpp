#ifndef FAKE_FILTER_IMPLEMENTATION_WITH_CONSTRUCTOR_PARAMETERS_HPP
#define FAKE_FILTER_IMPLEMENTATION_WITH_CONSTRUCTOR_PARAMETERS_HPP

#include "FakeFilterImplementation.hpp"

template <typename SourceImageType, typename DestinationImageType,
        typename... ConstructorParameters>
class FakeFilterImplementationWithConstructorParameters
        : public FakeFilterImplementation<SourceImageType,
                DestinationImageType> {
private:
    using SuperClass = FakeFilterImplementation<SourceImageType,
            DestinationImageType>;

public:
    FakeFilterImplementationWithConstructorParameters(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            const ConstructorParameters&...)
            : SuperClass(sourceImage, destinationImage) {
    }
};

#endif
