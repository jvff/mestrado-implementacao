#include "OpenCLKernelParametersKernelConfigurationTests.hpp"

TEST_C(doesNotSetParametersIfNonAreSpecified) {
    using EmptyParametersType = OpenCLKernelParameters<>;

    auto fakeContext = cl::Context();
    auto fakeKernel = FakeKernel();
    auto emptyParameters = EmptyParametersType(fakeContext);

    emptyParameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments();
}

TEST_C(setsSingleParameter) {
    using SingleParametersType = OpenCLKernelParameters<unsigned int>;

    auto fakeContext = cl::Context();
    auto fakeKernel = FakeKernel();
    auto parameterValue = 150u;
    auto parameters = SingleParametersType(fakeContext, parameterValue);

    parameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments(0, parameterValue);
}
