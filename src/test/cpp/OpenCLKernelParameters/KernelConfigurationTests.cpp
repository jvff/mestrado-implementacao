#include "OpenCLKernelParametersKernelConfigurationTests.hpp"

TEST_C(doesNotSetParametersIfNonAreSpecified) {
    using EmptyParametersType = TestOpenCLKernelParameters<>;

    auto emptyParameters = EmptyParametersType(fakeContext);

    emptyParameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments();
}

TEST_C(setsSingleParameter) {
    using SingleParametersType = TestOpenCLKernelParameters<unsigned int>;

    auto parameterValue = 150u;
    auto parameters = SingleParametersType(fakeContext, parameterValue);

    parameters.configureKernel(fakeKernel);

    fakeKernel.verifyArguments(0, parameterValue);
}

TEST_C(setsFourParameters) {
    using ParametersType =
            TestOpenCLKernelParameters<char, float, int, unsigned int>;

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

TEST_C(replacesPointerWithBuffer) {
    using ParametersType =
            TestOpenCLKernelParameters<char*, int, float*, unsigned int*, char>;

    auto charValue = 'y';
    auto floatValue = 3.1f;
    auto uintValue = 912u;

    auto firstValue = &charValue;
    auto secondValue = -20;
    auto thirdValue = &floatValue;
    auto fourthValue = &uintValue;
    auto fifthValue = 'x';

    auto parameters = ParametersType(fakeContext, firstValue, secondValue,
            thirdValue, fourthValue, fifthValue);

    parameters.configureKernel(fakeKernel);

    auto firstValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*firstValue));
    auto thirdValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*thirdValue));
    auto fourthValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*fourthValue));

    fakeKernel.verifyArguments(0, firstValueBuffer, 1, secondValue,
            2, thirdValueBuffer, 3, fourthValueBuffer, 4, fifthValue);
}
