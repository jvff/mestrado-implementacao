#ifndef LUMINANCE_FILTER_BASIC_TESTS_HPP
#define LUMINANCE_FILTER_BASIC_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AbstractFilter.hpp"
#include "Filter.hpp"
#include "Image.hpp"
#include "LuminanceFilter.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"
#include "RgbImage.hpp"
#include "SimpleFilter.hpp"

#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

#define TEST_C(TestName) \
    TEST_F(LuminanceFilterBasicTests, TestName)

class LuminanceFilterBasicTests : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;
};

#endif
