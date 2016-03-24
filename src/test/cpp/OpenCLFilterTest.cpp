#include "OpenCLFilterTest.hpp"

cl::Context OpenCLFilterTest::context;
cl::CommandQueue OpenCLFilterTest::commandQueue;
std::string OpenCLFilterTest::kernelSourceCode;

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
    auto width = 4u;
    auto height = 5u;
    auto kernelFunctionName = "labelPixelsWithCoordinateSum";

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

TEST_F(OpenCLFilterTest, appliesKernelToImageAndReturnsCreatedImage) {
    auto width = 4u;
    auto height = 5u;
    auto kernelFunctionName = "labelPixelsWithCoordinateSum";

    auto filter = FilterType(kernelSourceCode, kernelFunctionName);
    auto sourceImage = ImageType(width, height, context, commandQueue);

    auto resultImage = filter.apply(sourceImage);

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y) {
            auto pixelValue = resultImage.getPixelValue(x, y);
            auto expectedPixelValue = x + y;

            assertThat(pixelValue).isEqualTo(expectedPixelValue);
        }
    }
}

TEST_F(OpenCLFilterTest, appliesKernelWithParametersToImages) {
    using CustomFilterType = OpenCLFilter<unsigned int, unsigned int>;

    auto width = 4u;
    auto height = 5u;
    auto kernelFunctionName = "labelsPixelsInOrder";

    auto filter = CustomFilterType(kernelSourceCode, kernelFunctionName, width);
    auto sourceImage = ImageType(1, 1, context, commandQueue);
    auto destinationImage = ImageType(width, height, context, commandQueue);

    filter.apply(sourceImage, destinationImage);

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y) {
            auto pixelValue = destinationImage.getPixelValue(x, y);
            auto expectedPixelValue = x + y * width;

            assertThat(pixelValue).isEqualTo(expectedPixelValue);
        }
    }
}

TEST_F(OpenCLFilterTest, byDefaultHasOneWorkItemPerPixel) {
    using CustomFilterType = FakeOpenCLFilter<unsigned int>;

    auto width = 100;
    auto height = 67;

    auto filter = CustomFilterType(kernelSourceCode, "");
    auto sourceImage = ImageType(2, 3, context, commandQueue);
    auto destinationImage = ImageType(width, height, context, commandQueue);

    auto defaultGlobalWorkSize = filter.getGlobalWorkSize(sourceImage,
            destinationImage);
    auto oneWorkItemPerPixel = cl::NDRange(width, height);

    assertThat(defaultGlobalWorkSize).isEqualTo(oneWorkItemPerPixel);
}

TEST_F(OpenCLFilterTest, appliesKernelWithCustomGlobalWorkSizeToImages) {
    using CustomFilterType = OpenCLFilterOnQuarterImage<unsigned int,
            unsigned int>;

    auto width = 4u;
    auto height = 5u;
    auto kernelFunctionName = "labelsPixelsInOrder";

    auto filter = CustomFilterType(kernelSourceCode, kernelFunctionName, width);
    auto sourceImage = ImageType(1, 1, context, commandQueue);
    auto destinationImage = ImageType(width, height, context, commandQueue);

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y)
            destinationImage.setPixel(x, y, 0u);
    }

    filter.apply(sourceImage, destinationImage);

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y) {
            auto pixelValue = destinationImage.getPixelValue(x, y);
            auto expectedPixelValue = x + y * width;

            if (x >= width / 2 || y >= height / 2)
                expectedPixelValue = 0u;

            assertThat(pixelValue).isEqualTo(expectedPixelValue);
        }
    }
}
