#ifndef OPEN_C_L_KERNEL_PARAMETERS_KERNEL_CONFIGURATION_TESTS_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_KERNEL_CONFIGURATION_TESTS_HPP

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLKernelParameters.hpp"

#include "OpenCLKernelParametersFakeBuffer.hpp"
#include "OpenCLKernelParametersFakeKernel.hpp"

#define TEST_C(TestName) \
    TEST_F(OpenCLKernelParametersKernelConfigurationTests, TestName)

class OpenCLKernelParametersKernelConfigurationTests : public ::testing::Test {
protected:
    template <typename... ArgumentTypes>
    using TestOpenCLKernelParameters =
            TestableOpenCLKernelParameters<FakeKernel, FakeBuffer,
                    cl::CommandQueue, ArgumentTypes...>;

protected:
    cl::Context fakeContext;
    FakeKernel fakeKernel;
};

#endif
