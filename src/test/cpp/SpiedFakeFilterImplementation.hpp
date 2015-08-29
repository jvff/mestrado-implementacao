#ifndef SPIED_FAKE_FILTER_IMPLEMENTATION_HPP
#define SPIED_FAKE_FILTER_IMPLEMENTATION_HPP

#include "fakeit.hpp"

#include "FakeFilterImplementation.hpp"

using namespace fakeit;

template <typename SourceImageType, typename DestinationImageType,
        template <typename, typename, typename...> class SuperClassTemplate =
                FakeFilterImplementation,
        typename... ParameterTypes>
class SpiedFakeFilterImplementation : public SuperClassTemplate<SourceImageType,
        DestinationImageType, ParameterTypes...> {
private:
    using SuperClass = SuperClassTemplate<SourceImageType, DestinationImageType,
            ParameterTypes...>;
    using ThisClass = SpiedFakeFilterImplementation<SourceImageType,
            DestinationImageType, SuperClassTemplate, ParameterTypes...>;

    std::shared_ptr<Mock<ThisClass> > mock;

public:
    SpiedFakeFilterImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage,
            const ParameterTypes&... parameters)
            : SuperClass(sourceImage, destinationImage, parameters...),
            mock(new Mock<ThisClass>()) {
    }

    void apply() override {
        mock->get().apply();
    }

    Mock<ThisClass>& getSpy() {
        return *mock;
    }
};

#endif
