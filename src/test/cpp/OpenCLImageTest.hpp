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

protected:
    static cl::Context context;
    static cl::CommandQueue commandQueue;

protected:
    static void SetUpTestCase() {
        context = cl::Context(CL_DEVICE_TYPE_CPU);
    }
};

#endif
