#include "OpenCLImageComparatorWorkSizeTests.hpp"

TEST_C(defaultWorkSizeIsImageDimensions) {
    using PixelType = unsigned int;

    auto width = 2388;
    auto height = 1493;
    auto expectedWorkSize = cl::NDRange(width, height);

    auto mockImage = createMockImage<PixelType>(width, height);
    auto& image = mockImage.get();

    auto comparator = FakeOpenCLImageComparator<PixelType>();

    auto workSize = comparator.getGlobalWorkSize(image, image);

    assertThat(workSize).isEqualTo(expectedWorkSize);
}

TEST_C(workSizeIsDifferentForBoolPixelType) {
    using PixelType = bool;

    auto pixelGroupsPerLine = 450;
    auto width = pixelGroupsPerLine * 8;
    auto height = 1829;
    auto expectedWorkSize = cl::NDRange(pixelGroupsPerLine, height);

    auto mockImage = createMockImage<PixelType>(width, height);
    auto& image = mockImage.get();

    auto comparator = FakeOpenCLImageComparator<PixelType>();

    auto workSize = comparator.getGlobalWorkSize(image, image);

    assertThat(workSize).isEqualTo(expectedWorkSize);
}
