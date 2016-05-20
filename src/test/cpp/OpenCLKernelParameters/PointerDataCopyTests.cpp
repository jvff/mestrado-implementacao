#include "OpenCLKernelParametersPointerDataCopyTests.hpp"

TEST_C(copiesDataFromPointers) {
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
    parameters.sendPointerData(fakeCommandQueue);

    auto firstValueCapture = Capture<FakeBuffer>();
    auto thirdValueCapture = Capture<FakeBuffer>();
    auto fourthValueCapture = Capture<FakeBuffer>();

    fakeKernel.verifyArguments(0, firstValueCapture, 1, secondValue,
            2, thirdValueCapture, 3, fourthValueCapture, 4, fifthValue);

    auto& firstValueBuffer = *firstValueCapture;
    auto& thirdValueBuffer = *thirdValueCapture;
    auto& fourthValueBuffer = *fourthValueCapture;

    fakeCommandQueue.verifyNonBlockingWriteCommands(
            charValue, firstValueBuffer, floatValue, thirdValueBuffer,
            uintValue, fourthValueBuffer);
}

TEST_C(copiesDataToPointers) {
    using ParametersType =
            TestOpenCLKernelParameters<char*, int, float*, unsigned int*, char>;

    auto charValue = 'y';
    auto floatValue = 3.1f;
    auto uintValue = 912u;

    auto firstValue = &charValue;
    auto secondValue = -210;
    auto thirdValue = &floatValue;
    auto fourthValue = &uintValue;
    auto fifthValue = 'x';

    auto parameters = ParametersType(firstValue, secondValue, thirdValue,
            fourthValue, fifthValue);

    parameters.configureKernel(fakeContext, fakeKernel);
    parameters.retrievePointerData(fakeCommandQueue);

    auto firstValueCapture = Capture<FakeBuffer>();
    auto thirdValueCapture = Capture<FakeBuffer>();
    auto fourthValueCapture = Capture<FakeBuffer>();

    fakeKernel.verifyArguments(0, firstValueCapture, 1, secondValue,
            2, thirdValueCapture, 3, fourthValueCapture, 4, fifthValue);

    auto& firstValueBuffer = *firstValueCapture;
    auto& thirdValueBuffer = *thirdValueCapture;
    auto& fourthValueBuffer = *fourthValueCapture;

    fakeCommandQueue.verifyNonBlockingReadCommands(
            charValue, firstValueBuffer, floatValue, thirdValueBuffer,
            uintValue, fourthValueBuffer);
}
