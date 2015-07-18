#include "asserts.hpp"

#include "Filter.hpp"
#include "BinarizationFilter.hpp"

#include "BinarizationFilterTest.hpp"

using fakeit::Mock;
using fakeit::When;

TEST_F(BinarizationFilterTest, classIsntAbstract) {
    typedef BinarizationFilter<DummyType, FakeImage<bool> >
            DummyBinarizationFilter;

    AssertThat<DummyBinarizationFilter>::isConstructible(WithoutParameters());
}

TEST_F(BinarizationFilterTest, destinationImageTypeTemplateParameterExists) {
    typedef FakeImage<DummyType> DummyFakeImage;
    typedef BinarizationFilter<DummyType, FakeImage<bool>, DummyFakeImage>
            DummyBinarizationFilter;

    AssertThat<DummyBinarizationFilter>::isConstructible(WithoutParameters());
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
    BinarizationFilter<DummyType, FakeImage<bool> > filter;
    unsigned int width = 100;
    unsigned int height = 240;
    const Image<DummyType>& sourceImage = createMockImage(width, height);

    auto destinationImage = filter.apply(sourceImage);

    assertThat(destinationImage.getWidth()).isEqualTo(width);
    assertThat(destinationImage.getHeight()).isEqualTo(height);
}
