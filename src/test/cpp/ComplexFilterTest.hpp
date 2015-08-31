#ifndef COMPLEX_FILTER_TEST_HPP
#define COMPLEX_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"
#include "fakeit.hpp"

#include "ComplexFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeComplexFilter.hpp"
#include "FakeFilterImplementationWithConstructorParameters.hpp"
#include "FakeImage.hpp"
#include "SpiedFakeFilterImplementation.hpp"

using namespace fakeit;

class ComplexFilterTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationType = SpiedFakeFilterImplementation<SourceImageType,
            DestinationImageType>;
    using DummyFilterType = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;
    using FakeDummyFilterType = FakeComplexFilter<SourceImageType,
            DestinationImageType, ImplementationType>;

protected:
    FakeDummyFilterType filter;
    Mock<FakeDummyFilterType> filterSpy;

    Mock<SourceImageType> sourceImageMock;
    SourceImageType& sourceImage;

    std::unique_ptr<DestinationImageType> destinationImagePtr;
    std::unique_ptr<Mock<DestinationImageType> > destinationImageSpy;

    std::unique_ptr<ImplementationType> implementationPtr;

protected:
    ComplexFilterTest() : filterSpy(filter),
            sourceImage(sourceImageMock.get()) {
    }

    ~ComplexFilterTest() noexcept {
    }

    void setUpSourceImageMock(unsigned int width, unsigned int height) {
        When(Method(sourceImageMock, getWidth)).Return(width);
        When(Method(sourceImageMock, getHeight)).Return(height);
    }

    void setUpDestinationImageSpy(unsigned int width, unsigned int height) {
        setUpSpy(destinationImagePtr, destinationImageSpy, width, height);
    }

    Mock<ImplementationType>& setUpImplementationSpy() {
        auto* instancePtr = new ImplementationType(sourceImage,
                *destinationImagePtr);

        implementationPtr.reset(instancePtr);

        auto& spy = instancePtr->getSpy();

        When(Method(spy, apply)).Return();

        return spy;
    }

    template <typename Type, typename... ParameterTypes>
    void setUpSpy(std::unique_ptr<Type>& objectPtr,
            std::unique_ptr<Mock<Type> >& spyPtr,
            ParameterTypes&... parameters) {
        objectPtr.reset(new Type(parameters...));
        spyPtr.reset(new Mock<Type>(*objectPtr));
    }

    void mockInstantiation() {
        auto& genericImplementation = *implementationPtr;
        auto& specificImplementation =
                dynamic_cast<ImplementationType&>(genericImplementation);

        When(Method(filterSpy, instantiateImplementation))
            .Return(std::ref(specificImplementation));
    }
};

#endif
