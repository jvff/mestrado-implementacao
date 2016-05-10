#include "OpenCLFilterBasicTests.hpp"

TEST_C(classTemplateExists) {
    AssertThat<FilterType>::isClassOrStruct();
}

TEST_C(classTemplateHasVariadicTemplateArguments) {
    using FirstExtraParameter = unsigned int;
    using SecondExtraParameter = char;
    using ThirdExtraParameter = float;
    using FilterTypeWithExtraParameters = OpenCLFilter<PixelType,
            FirstExtraParameter, SecondExtraParameter, ThirdExtraParameter>;

    AssertThat<FilterTypeWithExtraParameters>::isClassOrStruct();
}

TEST_C(isFilter) {
    using ParentFilter = AbstractFilter<ImageType, ImageType>;

    AssertThat<FilterType>::isSubClass(Of<ParentFilter>());
}

TEST_C(isConstructibleWithKernelSourceCode) {
    using KernelSourceCodeParameter = const std::string&;
    using KernelFunctionNameParameter = const std::string&;

    AssertThat<FilterType>::isConstructible(
            With<KernelSourceCodeParameter, KernelFunctionNameParameter>());
}

TEST_C(isConstructibleWithKernelSourceCodeAndParameters) {
    using KernelSourceCodeParameter = const std::string&;
    using KernelFunctionNameParameter = const std::string&;
    using FirstKernelParameter = unsigned int;
    using SecondKernelParameter = float;
    using FilterTypeWithExtraParameters = OpenCLFilter<PixelType,
            FirstKernelParameter, SecondKernelParameter>;

    AssertThat<FilterTypeWithExtraParameters>::isConstructible(
            With<KernelSourceCodeParameter, KernelFunctionNameParameter,
                    FirstKernelParameter, SecondKernelParameter>());
}
