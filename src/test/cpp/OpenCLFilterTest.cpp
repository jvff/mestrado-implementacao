#include "OpenCLFilterTest.hpp"

cl::Context OpenCLFilterTest::context;
cl::CommandQueue OpenCLFilterTest::commandQueue;

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

TEST_F(OpenCLFilterTest, isConstructibleWithKernelSourceCodeAndParameters) {
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

TEST_F(OpenCLFilterTest, appliesKernelToImages) {
    std::string kernelFunctionName = "setThreadIdToPixel";
    std::string kernelSourceCode =
        "__kernel void setThreadIdToPixel(__read_only image2d_t sourceImage,\n"
        "       __write_only image2d_t destinationImage) {\n"
        "   int2 coordinate;\n"
        "   uint4 channels;\n"
        "\n"
        "   coordinate.x = get_global_id(0);\n"
        "   coordinate.y = get_global_id(1);\n"
        "\n"
        "   channels.x = coordinate.x + coordinate.y;\n"
        "\n"
        "   write_imageui(destinationImage, coordinate, channels);\n"
        "}\n";

    auto width = 4u;
    auto height = 5u;
    auto filter = FilterType(kernelSourceCode, kernelFunctionName);
    auto sourceImage = ImageType(1, 1, context, commandQueue);
    auto destinationImage = ImageType(width, height, context, commandQueue);

    filter.apply(sourceImage, destinationImage);

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y) {
            auto pixelValue = destinationImage.getPixelValue(x, y);
            auto expectedPixelValue = x + y;

            assertThat(pixelValue).isEqualTo(expectedPixelValue);
        }
    }
}
