#include "asserts.hpp"

#include "BinarizationFilter.hpp"
#include "SimpleArrayImage.hpp"

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
    unsigned int width = 30;
    unsigned int height = 40;
    SimpleArrayImage<int> sourceImage(width, height);
    SimpleArrayImage<bool> expectedImage(width, height);

    sourceImage = [] (unsigned int x, unsigned int y) {
        return (int)x - (int)y;
    };

    expectedImage = [] (unsigned int x, unsigned int y) {
        return x >= y;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}

TEST_F(BinarizationFilterTest, pixelsAreSetWhenDifferentThresholdIsUsed) {
    int threshold = 22;
    BinarizationFilter<int, SimpleArrayImage<bool> > filter(threshold);
    unsigned int width = 33;
    unsigned int height = 51;
    SimpleArrayImage<int> sourceImage(width, height);
    SimpleArrayImage<bool> expectedImage(width, height);

    sourceImage = [] (unsigned int x, unsigned int y) {
        return (int)x - (int)y;
    };

    expectedImage = [threshold] (unsigned int x, unsigned int y) {
        return ((int)x - (int)y) >= threshold;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}
