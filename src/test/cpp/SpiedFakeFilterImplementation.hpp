#ifndef SPIED_FAKE_FILTER_IMPLEMENTATION_HPP
#define SPIED_FAKE_FILTER_IMPLEMENTATION_HPP

#include "fakeit.hpp"

#include "FakeFilterImplementation.hpp"

using namespace fakeit;

template <typename SourceImageType, typename DestinationImageType>
class SpiedFakeFilterImplementation : public FakeFilterImplementation<
        SourceImageType, DestinationImageType> {
private:
    using SuperClass = FakeFilterImplementation<SourceImageType,
            DestinationImageType>;
    using ThisClass = SpiedFakeFilterImplementation<SourceImageType,
            DestinationImageType>;

    std::shared_ptr<Mock<ThisClass> > mock;

public:
    SpiedFakeFilterImplementation(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage)
            : SuperClass(sourceImage, destinationImage),
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
