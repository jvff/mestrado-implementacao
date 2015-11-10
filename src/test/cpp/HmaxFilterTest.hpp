#ifndef HMAX_FILTER_TEST_HPP
#define HMAX_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "HmaxFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class HmaxFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = HmaxFilter<SourceImageType, DestinationImageType>;
};

#endif
