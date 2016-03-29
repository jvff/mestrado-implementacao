#include "BinarizationFilterImplementationTest.hpp"

using SimpleImagesWithoutComparator =
        AliasesWithoutComparator<
                Image<int>, SimpleArrayImage<int>, SimpleArrayImage<bool> >;

template <template <typename> class ComparatorTemplate>
using SimpleImagesWithComparator =
        AliasesWithComparator<
                Image<int>, SimpleArrayImage<int>, SimpleArrayImage<bool>,
                ComparatorTemplate>;

using TypeParameters = ::testing::Types<
        SimpleImagesWithoutComparator,
        SimpleImagesWithComparator<std::less>,
        SimpleImagesWithComparator<std::greater>,
        SimpleImagesWithComparator<EqualsComparator> >;

TYPED_TEST_CASE(BinarizationFilterImplementationTest, TypeParameters);

TEST_C(imageDimensionsAreTheSame) {
    auto width = 10u;
    auto height = 24u;
    auto threshold = 0;

    auto filter = FilterType(threshold);
    const SourceImageType& sourceImage = RealSourceImageType(width, height);

    auto destinationImage = filter.apply(sourceImage);

    assertThat(destinationImage.getWidth()).isEqualTo(width);
    assertThat(destinationImage.getHeight()).isEqualTo(height);
}

TEST_C(filterResult) {
    int threshold = 0;

    auto filter = FilterType(threshold);
    auto test = TestImageType(30, 40, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST_C(filterResultWithDifferentThreshold) {
    int threshold = 22;

    auto filter = FilterType(threshold);
    auto test = TestImageType(33, 51, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST_C(filterResultWithNegativeThreshold) {
    int threshold = -9;

    auto filter = FilterType(threshold);
    auto test = TestImageType(65, 37, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}
