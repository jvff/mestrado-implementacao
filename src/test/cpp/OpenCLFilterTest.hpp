#ifndef OPEN_C_L_FILTER_TEST_HPP
#define OPEN_C_L_FILTER_TEST_HPP

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLFilter.hpp"

class OpenCLFilterTest : public ::testing::Test {
protected:
    using PixelType = unsigned int;
    using FilterType = OpenCLFilter<PixelType>;
};

#endif
