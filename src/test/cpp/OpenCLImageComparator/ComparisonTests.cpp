#include "OpenCLImageComparatorComparisonTests.hpp"

cl::Context OpenCLImageComparatorComparisonTests::context;
cl::CommandQueue OpenCLImageComparatorComparisonTests::commandQueue;

TEST_C(sameImageIsEqualToItself) {
    auto image = ImageType(1, 1, context, commandQueue);
    auto comparator = ComparatorType();

    assertThat(comparator.imagesAreEqual(image, image)).isEqualTo(true);
}
