#include "OpenCLKernelParametersBasicTests.hpp"

TEST_C(classTemplateExists) {
    using DummyParameters = OpenCLKernelParameters<>;

    AssertThat<DummyParameters>::isClassOrStruct();
}

TEST_C(hasVariadicTemplateParameters) {
    using FirstParameter = DummyTypes<0>;
    using SecondParameter = DummyTypes<1>*;
    using ThirdParameter = DummyTypes<2>;
    using DummyParameters = OpenCLKernelParameters<FirstParameter,
            SecondParameter, ThirdParameter>;

    AssertThat<DummyParameters>::isClassOrStruct();
}
