#include <gtest/gtest.h>

#include "asserts.hpp"
#include "fakeit.hpp"

#include "SimpleFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"
#include "FakeSimpleFilter.hpp"

using namespace fakeit;

TEST(SimpleFilterTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilterType = SimpleFilter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilterType>::isClassOrStruct();
}

TEST(SimpleFilterTest, isSubClassOfFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = SimpleFilter<SourceImageType, DestinationImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(SimpleFilterTest, destinationDimensionsAreSameAsSourceDimensions) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using FilterType = FakeSimpleFilter<SourceImageType, DestinationImageType>;

    unsigned int width = 10;
    unsigned int height = 8;

    FilterType filter;

    Mock<SourceImageType> sourceImageMock;
    const auto& sourceImage = sourceImageMock.get();

    When(Method(sourceImageMock, getWidth)).Return(width);
    When(Method(sourceImageMock, getHeight)).Return(height);

    auto result = filter.apply(sourceImage);

    assertThat(result.getWidth()).isEqualTo(width);
    assertThat(result.getHeight()).isEqualTo(height);
}
