#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RegionalMaximumsFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(RegionalMaximumsFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = RegionalMaximumsFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(RegionalMaximumsFilterTest, hasOptionalTemplateParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplicitType = RegionalMaximumsFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = RegionalMaximumsFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(RegionalMaximumsFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = RegionalMaximumsFilter<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(RegionalMaximumsFilterTest, isConstructibleWithoutParameters) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using ImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = RegionalMaximumsFilter<SourcePixelType,
            DestinationPixelType, ImageType>;

    AssertThat<DummyFilter>::isConstructible(WithoutParameters());
}

TEST(RegionalMaximumsFilterTest, uniformImageIsHugeRegionalMaximum) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = RegionalMaximumsFilter<PixelType, PixelType, ImageType>;

    FilterType filter;
    ImageType sourceImage(7, 4);
    ImageType& expectedImage = sourceImage;

    sourceImage = [] (unsigned int, unsigned int) {
        return 99;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}

TEST(RegionalMaximumsFilterTest, singleRegionalMaximum) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = RegionalMaximumsFilter<PixelType, PixelType, ImageType>;

    const unsigned int width = 9;
    const unsigned int height = 5;
    const unsigned int centerX = width / 2;
    const unsigned int centerY = height / 2;
    const PixelType peakHeight = 143;

    FilterType filter;
    ImageType sourceImage(width, height);
    ImageType expectedImage(width, height);

    sourceImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x == centerX && y == centerY)
            return peakHeight;
        else
            return 99;
    };

    expectedImage = [] (unsigned int x, unsigned int y) -> PixelType {
        if (x == centerX && y == centerY)
            return peakHeight;
        else
            return 0;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}
