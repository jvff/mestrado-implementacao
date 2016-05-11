#include "OpenCLKernelParametersBasicTests.hpp"

TEST_C(classTemplateExists) {
    using DummyParameters = OpenCLKernelParameters<>;

    AssertThat<DummyParameters>::isClassOrStruct();
}
