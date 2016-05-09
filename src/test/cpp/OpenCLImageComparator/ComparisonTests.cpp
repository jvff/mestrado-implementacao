#include "OpenCLImageComparatorComparisonTests.hpp"

cl::Context OpenCLImageComparatorComparisonTests::context;
cl::CommandQueue OpenCLImageComparatorComparisonTests::commandQueue;

TEST_C(sameImageIsEqualToItself) {
    auto image = ImageType(1, 1, context, commandQueue);
    auto comparator = ComparatorType();

    assertThat(comparator.imagesAreEqual(image, image)).isEqualTo(true);
}

TEST_C(singlePixelImagesAreEqual) {
    auto firstImage = ImageType(1, 1, context, commandQueue);
    auto secondImage = ImageType(1, 1, context, commandQueue);
    auto comparator = ComparatorType();

    firstImage.setPixel(0, 0, 0);
    secondImage.setPixel(0, 0, 0);

    auto result = comparator.imagesAreEqual(firstImage, secondImage);

    assertThat(result).isEqualTo(true);
}
