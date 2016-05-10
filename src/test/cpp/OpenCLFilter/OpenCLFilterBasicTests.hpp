#ifndef OPEN_C_L_FILTER_BASIC_TESTS_HPP
#define OPEN_C_L_FILTER_BASIC_TESTS_HPP

#include <string>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AbstractFilter.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

class OpenCLFilterBasicTests : public testing::Test {
protected:
    using PixelType = unsigned int;
    using ImageType = OpenCLImage<PixelType>;
    using FilterType = OpenCLFilter<PixelType>;
};

#define TEST_C(TestName) \
    TEST_F(OpenCLFilterBasicTests, TestName)

#endif
