#ifndef OPEN_C_L_KERNEL_PARAMETERS_POINTER_DATA_COPY_TESTS_HPP
#define OPEN_C_L_KERNEL_PARAMETERS_POINTER_DATA_COPY_TESTS_HPP

#include "OpenCLKernelParametersFakeCommandQueue.hpp"
#include "OpenCLKernelParametersKernelConfigurationTests.hpp"

#undef TEST_C
#define TEST_C(TestName) \
    TEST_F(OpenCLKernelParametersPointerDataCopyTests, TestName)

class OpenCLKernelParametersPointerDataCopyTests
        : public OpenCLKernelParametersKernelConfigurationTests {
protected:
    template <typename... ArgumentTypes>
    using TestOpenCLKernelParameters =
            TestableOpenCLKernelParameters<FakeKernel, FakeBuffer,
                    FakeCommandQueue, ArgumentTypes...>;

protected:
    FakeCommandQueue fakeCommandQueue;
};

#endif
