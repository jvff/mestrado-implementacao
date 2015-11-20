#ifndef LUMINANCE_FILTER_TEST_HPP
#define LUMINANCE_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "LuminanceFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class LuminanceFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;
};

#endif
