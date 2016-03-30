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

    initialize(width, height, 0);

    const SourceImageType& sourceImage = RealSourceImageType(width, height);

    auto destinationImage = filter->apply(sourceImage);

    assertThat(destinationImage.getWidth()).isEqualTo(width);
    assertThat(destinationImage.getHeight()).isEqualTo(height);
}

TEST_C(filterResult) {
    initialize(30, 40, 0);

    auto result = filter->apply(*sourceImage);

    assertThat(result).isEqualTo(*expectedImage);
}

TEST_C(filterResultWithDifferentThreshold) {
    initialize(33, 51, 22);

    auto result = filter->apply(*sourceImage);

    assertThat(result).isEqualTo(*expectedImage);
}

TEST_C(filterResultWithNegativeThreshold) {
    initialize(65, 37, -9);

    auto result = filter->apply(*sourceImage);

    assertThat(result).isEqualTo(*expectedImage);
}
