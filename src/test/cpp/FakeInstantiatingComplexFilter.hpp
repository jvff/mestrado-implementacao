#ifndef FAKE_INSTANTIATING_COMPLEX_FILTER_HPP
#define FAKE_INSTANTIATING_COMPLEX_FILTER_HPP

#include "FakeComplexFilter.hpp"

template <typename SourceImageType, typename DestinationImageType,
        typename ImplementationType, typename... ParameterTypes>
class FakeInstantiatingComplexFilter : public FakeComplexFilter<SourceImageType,
        DestinationImageType, ImplementationType> {
private:
    using ParameterTupleType = std::tuple<ParameterTypes...>;

    static constexpr auto numParameters = std::tuple_size<ParameterTupleType>::value;

    template <bool Condition>
    using EnableFor = typename std::enable_if<Condition, ImplementationType>
            ::type;

    template <int Index>
    using EnableForValid = EnableFor<Index < numParameters>;

    template <int Index>
    using EnableForInvalid = EnableFor<Index >= numParameters>;

private:
    std::tuple<ParameterTypes...> parameterTuple;

public:
    FakeInstantiatingComplexFilter(const ParameterTypes&... instanceParameters)
            : parameterTuple(std::make_tuple(instanceParameters...)) {
    }

    ImplementationType instantiateImplementation(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        return instantiate<0>(sourceImage, destinationImage);
    }

private:
    template <int ParameterIndex, typename... ParameterTypesSubSet>
    EnableForValid<ParameterIndex> instantiate(
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            const ParameterTypesSubSet&... parameters) {
        auto& parameter = std::get<ParameterIndex>(parameterTuple);
        using ParameterType = decltype(parameter);

        return instantiate<ParameterIndex + 1, ParameterTypesSubSet...,
                ParameterType>(sourceImage, destinationImage, parameters...,
                        parameter);
    }

    template <int ParameterIndex, typename...>
    ImplementationType instantiate(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            const ParameterTypes&... parameters) {
        return ImplementationType(sourceImage, destinationImage, parameters...);
    }
};

#endif
