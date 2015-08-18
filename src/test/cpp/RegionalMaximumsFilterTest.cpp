#include "RegionalMaximumsFilterTest.hpp"

template <typename PixelType, typename ImageType = SimpleArrayImage<PixelType> >
using TestData = RegionalMaximumsFilterTestData<PixelType, ImageType>;

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
    const unsigned int width = 7;
    const unsigned int height = 4;

    TestData<unsigned char>()
        .setDimensions(width, height)
        .drawPlateau(0, 0, width, height, 99);
}

TEST(RegionalMaximumsFilterTest, singleRegionalMaximum) {
    const unsigned int width = 9;
    const unsigned int height = 5;
    const unsigned int centerX = width / 2;
    const unsigned int centerY = height / 2;

    TestData<unsigned char>()
        .setDimensions(width, height)
        .setBackground(99)
        .setPeak(centerX, centerY, 143);
}

TEST(RegionalMaximumsFilterTest, multipleEqualMaximums) {
    const unsigned char peakHeight = 250;

    TestData<unsigned char>()
        .setDimensions(10, 6)
        .setBackground(200)
        .setPeak(0, 0, peakHeight)
        .setPeak(9, 5, peakHeight)
        .setPeak(0, 5, peakHeight)
        .setPeak(9, 0, peakHeight)
        .setPeak(3, 4, peakHeight)
        .setPeak(6, 2, peakHeight)
        .setPeak(2, 2, peakHeight);
}

TEST(RegionalMaximumsFilterTest, multipleDifferentMaximums) {
    TestData<unsigned char>()
        .setDimensions(10, 7)
        .setBackground(200)
        .setPeak(0, 0, 201)
        .setPeak(9, 6, 202)
        .setPeak(0, 6, 203)
        .setPeak(9, 0, 204)
        .setPeak(3, 4, 205)
        .setPeak(6, 2, 206)
        .setPeak(2, 2, 207);
}
