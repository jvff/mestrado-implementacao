#ifndef FILTER_IMPLEMENTATION_TEST_HPP
#define FILTER_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"
#include "fakeit.hpp"

#include "FilterImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "FakeFilterImplementation.hpp"

using namespace fakeit;

class FilterImplementationTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementationType = FilterImplementation<SourceImageType,
            DestinationImageType>;
    using FakeDummyImplementationType = FakeFilterImplementation<
            SourceImageType, DestinationImageType>;
};

#endif
