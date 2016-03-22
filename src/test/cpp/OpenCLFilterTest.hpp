#ifndef OPEN_C_L_FILTER_TEST_HPP
#define OPEN_C_L_FILTER_TEST_HPP

#include <string>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AbstractFilter.hpp"
#include "OpenCLFilter.hpp"
#include "OpenCLImage.hpp"

#include "cl/OpenCLFilterTestKernels.h"

class OpenCLFilterTest : public ::testing::Test {
protected:
    using PixelType = unsigned int;
    using ImageType = OpenCLImage<PixelType>;
    using FilterType = OpenCLFilter<PixelType>;

protected:
    static cl::Context context;
    static cl::CommandQueue commandQueue;
    static std::string kernelSourceCode;

protected:
    static void SetUpTestCase() {
        auto defaultDevice = cl::Device::getDefault();

        context = cl::Context::getDefault();
        commandQueue = cl::CommandQueue(context, defaultDevice);

        kernelSourceCode = OpenCLFilterTestKernelsSourceCode;
    }
};

#endif
