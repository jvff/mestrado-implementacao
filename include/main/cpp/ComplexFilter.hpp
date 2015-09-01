#ifndef COMPLEX_FILTER_HPP
#define COMPLEX_FILTER_HPP

#include <type_traits>

#include "Filter.hpp"

template <typename SourceImageType, typename DestinationImageType,
        typename ImplementationType>
class AbstractComplexFilter : public Filter<SourceImageType,
        DestinationImageType> {
private:
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

public:
    using SuperClass::apply;

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        instantiateImplementation(sourceImage, destinationImage).apply();
    }

protected:
    virtual ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) = 0;
};

template <typename SourceImageType, typename DestinationImageType,
        typename ImplementationType, typename ShouldEnable = void>
class ComplexFilter : public AbstractComplexFilter<SourceImageType,
        DestinationImageType, ImplementationType> {
};

template <typename SourceImageType, typename DestinationImageType,
        typename ImplementationType>
class ComplexFilter<SourceImageType, DestinationImageType, ImplementationType,
        typename std::enable_if<std::is_constructible<ImplementationType,
                const SourceImageType&, DestinationImageType&>::value>::type>
        : public AbstractComplexFilter<SourceImageType, DestinationImageType,
                ImplementationType> {
protected:
    virtual ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        return ImplementationType(sourceImage, destinationImage);
    }
};

#endif
