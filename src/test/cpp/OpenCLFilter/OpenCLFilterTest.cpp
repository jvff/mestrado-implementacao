#include "OpenCLFilterTest.hpp"

TEST_F(OpenCLFilterTest, appliesKernelToImages) {
    auto width = 4u;
    auto height = 5u;
    auto kernelFunctionName = "labelPixelsWithCoordinateSum";

    auto filter = FilterType(kernelSourceCode, kernelFunctionName);
    auto sourceImage = ImageType(1, 1, context, commandQueue);
    auto destinationImage = ImageType(width, height, context, commandQueue);

    filter.apply(sourceImage, destinationImage);

    verifyImagePixels(destinationImage, coordinateSumPixels);
}

TEST_F(OpenCLFilterTest, appliesKernelToImageAndReturnsCreatedImage) {
    auto width = 4u;
    auto height = 5u;
    auto kernelFunctionName = "labelPixelsWithCoordinateSum";

    auto filter = FilterType(kernelSourceCode, kernelFunctionName);
    auto sourceImage = ImageType(width, height, context, commandQueue);

    auto resultImage = filter.apply(sourceImage);

    assertThat(resultImage.getWidth()).isEqualTo(width);
    assertThat(resultImage.getHeight()).isEqualTo(height);

    verifyImagePixels(resultImage, coordinateSumPixels);
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

    verifyImagePixels(destinationImage, pixelsInOrder(width));
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

    auto halfWidth = width / 2;
    auto halfHeight = height / 2;

    auto firstQuarter = pixelsInOrder(width);
    auto secondQuarter = zeroedPixels;
    auto bottomHalf = zeroedPixels;

    verifyImagePixels(destinationImage, halfWidth, halfHeight, firstQuarter);
    verifyImagePixels(destinationImage, halfWidth, 0, width, halfHeight,
            secondQuarter);
    verifyImagePixels(destinationImage, 0, halfHeight, width, height,
            bottomHalf);
}

TEST_F(OpenCLFilterTest, hasNoDefaultLocalWorkSize) {
    using CustomFilterType = FakeOpenCLFilter<unsigned int>;

    auto filter = CustomFilterType(kernelSourceCode, "");
    auto sourceImage = ImageType(1, 1, context, commandQueue);
    auto destinationImage = ImageType(1, 1, context, commandQueue);

    auto defaultLocalWorkSize = filter.getLocalWorkSize(sourceImage,
            destinationImage);

    assertThat(defaultLocalWorkSize).isEqualTo(cl::NullRange);
}

TEST_F(OpenCLFilterTest, appliesKernelWithCustomLocalWorkSizeToImages) {
    using CustomFilterType = OpenCLFilterOnImageQuarters<unsigned int,
            unsigned int>;

    auto width = 4u;
    auto height = 6u;
    auto kernelFunctionName = "labelsPixelsInOrderWithLocalId";

    auto filter = CustomFilterType(kernelSourceCode, kernelFunctionName, width);
    auto sourceImage = ImageType(1, 1, context, commandQueue);
    auto destinationImage = ImageType(width, height, context, commandQueue);

    for (auto x = 0u; x < width; ++x) {
        for (auto y = 0u; y < height; ++y)
            destinationImage.setPixel(x, y, 0u);
    }

    filter.apply(sourceImage, destinationImage);

    verifyImagePixels(destinationImage, pixelsInQuartetInOrder(width, height));
}
