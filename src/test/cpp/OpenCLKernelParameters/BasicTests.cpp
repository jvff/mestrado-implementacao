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
    using ContextParameter = const cl::Context&;
    using FirstParameterType = int;
    using SecondParameterType = char;
    using DummyParameters = OpenCLKernelParameters<FirstParameterType,
            SecondParameterType>;

    AssertThat<DummyParameters>::isConstructible(
            With<ContextParameter, FirstParameterType, SecondParameterType>());
}
