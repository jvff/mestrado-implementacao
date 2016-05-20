#include "OpenCLKernelParametersKernelConfigurationTests.hpp"

TEST_C(doesNotSetParametersIfNonAreSpecified) {
    using EmptyParametersType = TestOpenCLKernelParameters<>;

    auto emptyParameters = EmptyParametersType();

    emptyParameters.configureKernel(fakeContext, fakeKernel);

    fakeKernel.verifyArguments();
}

TEST_C(setsSingleParameter) {
    using SingleParametersType = TestOpenCLKernelParameters<unsigned int>;

    auto parameterValue = 150u;
    auto parameters = SingleParametersType(parameterValue);

    parameters.configureKernel(fakeContext, fakeKernel);

    fakeKernel.verifyArguments(0, parameterValue);
}

TEST_C(setsFourParameters) {
    using ParametersType =
            TestOpenCLKernelParameters<char, float, int, unsigned int>;

    auto firstValue = 'z';
    auto secondValue = -0.004f;
    auto thirdValue = -20;
    auto fourthValue = 35u;
    auto parameters = ParametersType(firstValue, secondValue, thirdValue,
            fourthValue);

    parameters.configureKernel(fakeContext, fakeKernel);

    fakeKernel.verifyArguments(0, firstValue, 1, secondValue, 2, thirdValue,
            3, fourthValue);
}

TEST_C(setsThreeParametersAfterGivenOffset) {
    using ParametersType =
            TestOpenCLKernelParameters<unsigned char, short, unsigned short>;

    unsigned char firstValue = 254;
    short secondValue = -123;
    unsigned short thirdValue = 65533;
    auto parameters = ParametersType(firstValue, secondValue, thirdValue);

    auto startingIndex = 11u;

    parameters.configureKernel(fakeContext, fakeKernel, startingIndex);

    fakeKernel.verifyArguments(startingIndex, firstValue,
            startingIndex + 1, secondValue, startingIndex + 2, thirdValue);
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

    auto parameters = ParametersType(firstValue, secondValue, thirdValue,
            fourthValue, fifthValue);

    parameters.configureKernel(fakeContext, fakeKernel);

    auto firstValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*firstValue));
    auto thirdValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*thirdValue));
    auto fourthValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*fourthValue));

    fakeKernel.verifyArguments(0, firstValueBuffer, 1, secondValue,
            2, thirdValueBuffer, 3, fourthValueBuffer, 4, fifthValue);
}

TEST_C(replacesPointerWithBufferAlsoWithStartingIndex) {
    using ParametersType =
            TestOpenCLKernelParameters<int, float*, int*, char, unsigned int*>;

    auto floatValue = -0.17f;
    auto intValue = -10000;
    auto uintValue = 82u;

    auto firstValue = -20;
    auto secondValue = &floatValue;
    auto thirdValue = &intValue;
    auto fourthValue = 'b';
    auto fifthValue = &uintValue;

    auto parameters = ParametersType(firstValue, secondValue, thirdValue,
            fourthValue, fifthValue);

    auto startingIndex = 8u;

    parameters.configureKernel(fakeContext, fakeKernel, startingIndex);

    auto secondValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*secondValue));
    auto thirdValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*thirdValue));
    auto fifthValueBuffer = FakeBuffer(fakeContext, CL_MEM_READ_WRITE,
            sizeof(*fifthValue));

    fakeKernel.verifyArguments(startingIndex, firstValue,
            startingIndex + 1, secondValueBuffer,
            startingIndex + 2, thirdValueBuffer,
            startingIndex + 3, fourthValue,
            startingIndex + 4, fifthValueBuffer);
}
