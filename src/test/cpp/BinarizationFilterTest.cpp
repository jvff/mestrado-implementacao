#include "asserts.hpp"

#include "BinarizationFilterTest.hpp"

using fakeit::Mock;
using fakeit::When;

TEST_F(BinarizationFilterTest, classIsntAbstractAndConstructorHasParameter) {
    typedef BinarizationFilter<DummyType, FakeImage<bool> >
            DummyBinarizationFilter;
    typedef const DummyType& parameter;

    AssertThat<DummyBinarizationFilter>::isConstructible(With<parameter>());
}

TEST_F(BinarizationFilterTest, destinationImageTypeTemplateParameterExists) {
    typedef FakeImage<DummyType> DummyFakeImage;
    typedef BinarizationFilter<DummyType, FakeImage<bool>, DummyFakeImage>
            DummyBinarizationFilter;
    typedef const DummyType& parameter;

    AssertThat<DummyBinarizationFilter>::isConstructible(With<parameter>());
}

TEST_F(BinarizationFilterTest, defaultDestinationImageTypeIsSimpleArrayImage) {
    typedef BinarizationFilter<DummyType, FakeImage<bool> > implicitType;
    typedef BinarizationFilter<DummyType, FakeImage<bool>, Image<DummyType> >
            explicitType;

    AssertThat<implicitType>::isTheSame(As<explicitType>());
}

TEST_F(BinarizationFilterTest, classIsAFilter) {
    typedef Filter<DummyType, bool, FakeImage<bool> > filterType;
    typedef BinarizationFilter<DummyType, FakeImage<bool> >
            binarizationFilterType;

    AssertThat<binarizationFilterType>::isSubClass(Of<filterType>());
}

TEST_F(BinarizationFilterTest, imageDimensionsAreTheSame) {
    BinarizationFilter<DummyType, FakeImage<bool> > filter(DummyType{0});
    unsigned int width = 10;
    unsigned int height = 24;
    const Image<DummyType>& sourceImage = createMockImage(width, height);

    auto destinationImage = filter.apply(sourceImage);

    assertThat(destinationImage.getWidth()).isEqualTo(width);
    assertThat(destinationImage.getHeight()).isEqualTo(height);
}

TEST_F(BinarizationFilterTest, pixelsAreSet) {
    int threshold = 0;
    BinarizationFilter<int, SimpleArrayImage<bool> > filter(threshold);
    TestImage<int> test(30, 40, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST_F(BinarizationFilterTest, pixelsAreSetWhenDifferentThresholdIsUsed) {
    int threshold = 22;
    BinarizationFilter<int, SimpleArrayImage<bool> > filter(threshold);
    TestImage<int> test(33, 51, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}

TEST_F(BinarizationFilterTest, pixelsAreSetWhenNegativeThresholdIsUsed) {
    int threshold = -9;
    BinarizationFilter<int, SimpleArrayImage<bool> > filter(threshold);
    TestImage<int> test(65, 37, threshold);

    auto result = filter.apply(test.sourceImage);

    assertThat(result).isEqualTo(test.expectedImage);
}
