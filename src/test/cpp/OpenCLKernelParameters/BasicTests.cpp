#include "OpenCLKernelParametersBasicTests.hpp"

TEST_C(classTemplateExists) {
    using DummyParameters = OpenCLKernelParameters<>;

    AssertThat<DummyParameters>::isClassOrStruct();
}

TEST_C(hasVariadicTemplateParameters) {
    using FirstParameterType = DummyTypes<0>;
    using SecondParameterType = DummyTypes<1>*;
    using ThirdParameterType = DummyTypes<2>;
    using DummyParameters = OpenCLKernelParameters<FirstParameterType,
            SecondParameterType, ThirdParameterType>;

    AssertThat<DummyParameters>::isClassOrStruct();
}

TEST_C(hasValueConstructor) {
    using FirstParameterType = int;
    using SecondParameterType = char;
    using DummyParameters = OpenCLKernelParameters<FirstParameterType,
            SecondParameterType>;

    AssertThat<DummyParameters>::isConstructible(
            With<FirstParameterType, SecondParameterType>());
}

TEST_C(isAliasToTestableClass) {
    using FirstParameterType = unsigned int;
    using SecondParameterType = float;
    using ThirdParameterType = short int;
    using FourthParameterType = char*;

    using KernelType = cl::Kernel;
    using BufferType = cl::Buffer;
    using CommandQueueType = cl::CommandQueue;

    using Alias = OpenCLKernelParameters<FirstParameterType,
            SecondParameterType, ThirdParameterType, FourthParameterType>;
    using TestableClass = TestableOpenCLKernelParameters<KernelType, BufferType,
            CommandQueueType, FirstParameterType, SecondParameterType,
            ThirdParameterType, FourthParameterType>;

    AssertThat<Alias>::isTheSame(As<TestableClass>());
}
