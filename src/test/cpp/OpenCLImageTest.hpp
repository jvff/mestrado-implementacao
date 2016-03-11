#ifndef OPEN_C_L_IMAGE_TEST_HPP
#define OPEN_C_L_IMAGE_TEST_HPP

#include <CL/cl.hpp>
#include <CL/opencl.h>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "OpenCLImage.hpp"

class OpenCLImageTest : public ::testing::Test {
protected:
    using PixelType = unsigned char;
    using ImageType = OpenCLImage<PixelType>;
};

#endif
