#ifndef ABSTRACT_FILTER_TEST_HPP
#define ABSTRACT_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AbstractFilter.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImageMockProxy.hpp"

class AbstractFilterTest : public testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImageMockProxy<DestinationPixelType>;
    using DummyFilter = AbstractFilter<SourceImageType, DestinationImageType>;
};

#endif
