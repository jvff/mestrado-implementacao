#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "Filter.hpp"
#include "BinarizationFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

using fakeit::Mock;
using fakeit::When;

TEST(BinarizationFilterTest, classIsntAbstract) {
    auto filter = new BinarizationFilter<DummyType, FakeImage<bool> >();

    assertThat(filter).isNotNull();

    delete filter;
}

TEST(BinarizationFilterTest, destinationImageTypeTemplateParameterExists) {
    auto filter = new BinarizationFilter<DummyType, FakeImage<bool>,
            FakeImage<DummyType> >();

    assertThat(filter).isNotNull();

    delete filter;
}

TEST(BinarizationFilterTest, defaultDestinationImageTypeIsSimpleArrayImage) {
    typedef BinarizationFilter<DummyType, FakeImage<bool> > implicitType;
    typedef BinarizationFilter<DummyType, FakeImage<bool>, Image<DummyType> >
            explicitType;

    AssertThat<implicitType>::isTheSame(As<explicitType>());
}

TEST(BinarizationFilterTest, classIsAFilter) {
    typedef Filter<DummyType, bool, FakeImage<bool> > filterType;
    typedef BinarizationFilter<DummyType, FakeImage<bool> >
            binarizationFilterType;

    AssertThat<binarizationFilterType>::isSubClass(Of<filterType>());
}

TEST(BinarizationFilterTest, imageDimensionsAreTheSame) {
    BinarizationFilter<DummyType, FakeImage<bool> > filter;
    Mock<FakeImage<DummyType> > sourceImageMock;
    const Image<DummyType>& sourceImage = sourceImageMock.get();
    unsigned int width = 100;
    unsigned int height = 240;

    When(Method(sourceImageMock, getWidth)).Return(width);
    When(Method(sourceImageMock, getHeight)).Return(height);

    auto* destinationImage = filter.apply(&sourceImage);

    assertThat(destinationImage->getWidth()).isEqualTo(width);
    assertThat(destinationImage->getHeight()).isEqualTo(height);

    delete destinationImage;
}
