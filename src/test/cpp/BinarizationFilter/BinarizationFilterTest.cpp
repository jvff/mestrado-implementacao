#include "BinarizationFilterTest.hpp"

TEST(BinarizationFilterTest, imageDimensionsAreTheSame) {
    auto width = 10u;
    auto height = 24u;
    auto threshold = DummyType{ 0 };

    BinarizationFilter<Image<DummyType>, FakeImage<bool> > filter(threshold);
    const Image<DummyType>& sourceImage = FakeImage<DummyType>(width, height);

    auto destinationImage = filter.apply(sourceImage);

    assertThat(destinationImage.getWidth()).isEqualTo(width);
    assertThat(destinationImage.getHeight()).isEqualTo(height);
}

TEST(BinarizationFilterTest, filterResult) {
    int threshold = 0;
    BinarizationFilter<Image<int>, SimpleArrayImage<bool> > filter(threshold);
    TestImage<int> test(30, 40, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST(BinarizationFilterTest, filterResultWithDifferentThreshold) {
    int threshold = 22;
    BinarizationFilter<Image<int>, SimpleArrayImage<bool> > filter(threshold);
    TestImage<int> test(33, 51, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST(BinarizationFilterTest, filterResultWithNegativeThreshold) {
    int threshold = -9;
    BinarizationFilter<Image<int>, SimpleArrayImage<bool> > filter(threshold);
    TestImage<int> test(65, 37, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST(BinarizationFilterTest, filterResultWithCustomComparator) {
    using FilterType = BinarizationFilter<Image<int>, SimpleArrayImage<bool>,
            EqualsComparator>;

    int threshold = 0;

    FilterType filter(threshold);
    TestImage<int, EqualsComparator> test(30, 40, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST(BinarizationFilterTest, filterResultWithComparatorAndDifferentThreshold) {
    using FilterType = BinarizationFilter<Image<int>, SimpleArrayImage<bool>,
            EqualsComparator>;

    int threshold = 22;

    FilterType filter(threshold);
    TestImage<int, EqualsComparator> test(33, 51, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST(BinarizationFilterTest, filterResultWithComparatorAndNegativeThreshold) {
    using FilterType = BinarizationFilter<Image<int>, SimpleArrayImage<bool>,
            std::less>;

    int threshold = -9;

    FilterType filter(threshold);
    TestImage<int, std::less> test(65, 37, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}
