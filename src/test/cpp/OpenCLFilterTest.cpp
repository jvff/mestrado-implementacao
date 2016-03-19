#include "OpenCLFilterTest.hpp"

TEST_F(OpenCLFilterTest, classTemplateExists) {
    AssertThat<FilterType>::isClassOrStruct();
}

TEST_F(OpenCLFilterTest, classTemplateHasVariadicTemplateArguments) {
    using FirstExtraParameter = unsigned int;
    using SecondExtraParameter = char;
    using ThirdExtraParameter = float;
    using FilterTypeWithExtraParameters = OpenCLFilter<PixelType,
            FirstExtraParameter, SecondExtraParameter, ThirdExtraParameter>;

    AssertThat<FilterTypeWithExtraParameters>::isClassOrStruct();
}

TEST_F(OpenCLFilterTest, isFilter) {
    using ParentFilter = AbstractFilter<ImageType, ImageType>;

    AssertThat<FilterType>::isSubClass(Of<ParentFilter>());
}

TEST_F(OpenCLFilterTest, isConstructibleWithKernelSourceCode) {
    using KernelSourceCodeParameter = const std::string&;
    using KernelFunctionNameParameter = const std::string&;

    AssertThat<FilterType>::isConstructible(
            With<KernelSourceCodeParameter, KernelFunctionNameParameter>());
}
