#ifndef LUMINANCE_FILTER_TEST_HPP
#define LUMINANCE_FILTER_TEST_HPP

#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "Filter.hpp"
#include "LuminanceFilter.hpp"
#include "RgbImage.hpp"
#include "SimpleArrayImage.hpp"
#include "SimpleFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

using namespace fakeit;

class LuminanceFilterTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;
};

#endif