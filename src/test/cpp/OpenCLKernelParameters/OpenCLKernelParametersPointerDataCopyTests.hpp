#ifndef OPEN_C_L_KERNEL_PARAMETERS_POINTER_DATA_COPY_TESTS_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_POINTER_DATA_COPY_TESTS_HPP

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLKernelParameters.hpp"

#include "OpenCLKernelParametersFakeBuffer.hpp"
#include "OpenCLKernelParametersFakeCommandQueue.hpp"
#include "OpenCLKernelParametersFakeKernel.hpp"

#define TEST_C(TestName) \
    TEST_F(OpenCLKernelParametersPointerDataCopyTests, TestName)

class OpenCLKernelParametersPointerDataCopyTests : public ::testing::Test {
protected:
    template <typename... ArgumentTypes>
    using TestOpenCLKernelParameters =
            TestableOpenCLKernelParameters<FakeKernel, FakeBuffer,
                    FakeCommandQueue, ArgumentTypes...>;

protected:
    cl::Context fakeContext;
    FakeCommandQueue fakeCommandQueue;
    FakeKernel fakeKernel;
};

#endif
