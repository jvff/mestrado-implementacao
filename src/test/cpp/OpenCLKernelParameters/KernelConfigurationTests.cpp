#include "OpenCLKernelParametersKernelConfigurationTests.hpp"

TEST_C(doesNotSetParametersIfNonAreSpecified) {
    using EmptyParametersType = OpenCLKernelParameters<>;

    auto emptyParameters = EmptyParametersType(fakeContext);

    emptyParameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments();
}

TEST_C(setsSingleParameter) {
    using SingleParametersType = OpenCLKernelParameters<unsigned int>;

    auto parameterValue = 150u;
    auto parameters = SingleParametersType(fakeContext, parameterValue);

    parameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments(0, parameterValue);
}

TEST_C(setsFourParameters) {
    using ParametersType =
            OpenCLKernelParameters<char, float, int, unsigned int>;

    auto firstValue = 'z';
    auto secondValue = -0.004f;
    auto thirdValue = -20;
    auto fourthValue = 35u;
    auto parameters = ParametersType(fakeContext, firstValue, secondValue,
            thirdValue, fourthValue);

    parameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments(0, firstValue, 1, secondValue, 2, thirdValue,
            3, fourthValue);
}
