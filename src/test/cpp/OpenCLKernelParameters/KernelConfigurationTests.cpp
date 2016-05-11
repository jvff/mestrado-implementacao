#include "OpenCLKernelParametersKernelConfigurationTests.hpp"

TEST_C(doesNotSetParametersIfNonAreSpecified) {
    using EmptyParametersType = OpenCLKernelParameters<>;

    auto fakeContext = cl::Context();
    auto fakeKernel = FakeKernel();
    auto emptyParameters = EmptyParametersType(fakeContext);

    emptyParameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments();
}
