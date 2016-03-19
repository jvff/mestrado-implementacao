#ifndef OPEN_C_L_FILTER_TEST_HPP
#define OPEN_C_L_FILTER_TEST_HPP

#include <string>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AbstractFilter.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

class OpenCLFilterTest : public ::testing::Test {
protected:
    using PixelType = unsigned int;
    using ImageType = OpenCLImage<PixelType>;
    using FilterType = OpenCLFilter<PixelType>;
};

#endif
