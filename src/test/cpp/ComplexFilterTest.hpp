#ifndef COMPLEX_FILTER_TEST_HPP
#define COMPLEX_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class ComplexFilterTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using ImplementationType = DummyTypes<3>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilterType = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;
};

#endif
