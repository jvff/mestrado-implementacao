#ifndef COMPLEX_FILTER_TEST_HPP
#define COMPLEX_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"
#include "fakeit.hpp"

#include "ComplexFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeComplexFilter.hpp"
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
    Mock<SourceImageType> createSourceImageMock(unsigned int width,
            unsigned int height) {
        return createImageMock<SourceImageType>(width, height);
    }

    Mock<DestinationImageType> createDestinationImageMock(unsigned int width,
            unsigned int height) {
        return createImageMock<DestinationImageType>(width, height);
    }

    template <typename ImageType>
    Mock<ImageType> createImageMock(unsigned int width, unsigned int height) {
        Mock<ImageType> mock;

        When(Method(mock, getWidth)).Return(width);
        When(Method(mock, getHeight)).Return(height);

        return mock;
    }
};

#endif
