#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleArrayImage.hpp"
#include "WatershedFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(WatershedFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = WatershedFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(WatershedFilterTest, defaultSourceImageTypeIsGenericImage) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using ImplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType>;
    using ExplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST(WatershedFilterTest, isSubClassOfFilter) {
    using SourcePixelType = DummyTypes<2>;
    using DestinationPixelType = DummyTypes<1>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SourceImageType = Image<SourcePixelType>;
    using SubClass = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(WatershedFilterTest, isConstructible) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = WatershedFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isConstructible(WithoutParameters());
}

TEST(WatershedFilterTest, singleSegment) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = WatershedFilter<PixelType, PixelType, ImageType>;

    unsigned int width = 5;
    unsigned int height = 5;

    ImageType sourceImage(width, height);
    ImageType expectedImage(width, height);
    FilterType filter;

    sourceImage = [] (unsigned int, unsigned int) {
        return 10;
    };

    expectedImage = [] (unsigned int, unsigned int) {
        return 1;
    };

    auto resultingImage = filter.apply(sourceImage);

    assertThat(resultingImage).isEqualTo(expectedImage);
}
