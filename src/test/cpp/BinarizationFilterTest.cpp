#include "BinarizationFilterTest.hpp"

TEST(BinarizationFilterTest, classIsntAbstractAndConstructorHasParameter) {
    using DummyBinarizationFilter = BinarizationFilter<Image<DummyType>,
            FakeImage<bool> >;
    using ThresholdParameter = const DummyType&;

    AssertThat<DummyBinarizationFilter>::isConstructible(
            With<ThresholdParameter>());
}

TEST(BinarizationFilterTest, isConstructibleWithComparatorParameter) {
    using DummyBinarizationFilter = BinarizationFilter<Image<DummyType>,
            FakeImage<bool> >;
    using ThresholdParameter = const DummyType&;
    using ComparatorParameter =
            const std::function<bool(const DummyType&, const DummyType&)>&;

    AssertThat<DummyBinarizationFilter>::isConstructible(
            With<ThresholdParameter, ComparatorParameter>());
}

TEST(BinarizationFilterTest, classIsSimpleFilter) {
    using SuperClass = SimpleFilter<Image<DummyType>, FakeImage<bool> >;
    using SubClass = BinarizationFilter<Image<DummyType>, FakeImage<bool> >;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(BinarizationFilterTest, imageDimensionsAreTheSame) {
    BinarizationFilter<Image<DummyType>, FakeImage<bool> > filter(DummyType{0});
    unsigned int width = 10;
    unsigned int height = 24;
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
    using FilterType = BinarizationFilter<Image<int>, SimpleArrayImage<bool> >;

    int threshold = 0;
    auto comparator = [] (int pixelValue, int threshold) -> bool {
        return pixelValue == threshold;
    };

    FilterType filter(threshold, comparator);
    TestImage<int> test(30, 40, threshold, comparator);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST(BinarizationFilterTest, filterResultWithComparatorAndDifferentThreshold) {
    using FilterType = BinarizationFilter<Image<int>, SimpleArrayImage<bool> >;

    int threshold = 22;
    auto comparator = [] (int pixelValue, int threshold) -> bool {
        return pixelValue <= threshold;
    };

    FilterType filter(threshold, comparator);
    TestImage<int> test(33, 51, threshold, comparator);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST(BinarizationFilterTest, filterResultWithComparatorAndNegativeThreshold) {
    using FilterType = BinarizationFilter<Image<int>, SimpleArrayImage<bool> >;

    int threshold = -9;
    auto comparator = [] (int pixelValue, int threshold) -> bool {
        return pixelValue < threshold;
    };

    FilterType filter(threshold, comparator);
    TestImage<int> test(65, 37, threshold, comparator);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}
