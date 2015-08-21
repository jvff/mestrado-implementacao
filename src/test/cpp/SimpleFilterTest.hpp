#ifndef SIMPLE_FILTER_TEST_HPP
#define SIMPLE_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"
#include "fakeit.hpp"

#include "SimpleFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "FakeSimpleFilter.hpp"
#include "RefTo.hpp"

using namespace fakeit;

class SimpleFilterTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilterType = SimpleFilter<SourceImageType, DestinationImageType>;

protected:
    Mock<SourceImageType> createSourceImageMock(unsigned int width,
            unsigned int height) {
        Mock<SourceImageType> mock;

        When(Method(mock, getWidth)).Return(width);
        When(Method(mock, getHeight)).Return(height);

        return mock;
    }
};

#endif
