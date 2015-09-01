#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaClosingFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AreaClosingFilter<Image<DummyType>, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(AreaClosingFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = AreaClosingFilter<SourceImageType, DestinationImageType>;
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(AreaClosingFilterTest, isConstructibleWithParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = AreaClosingFilter<SourceImageType,
            DestinationImageType>;
    using AreaSizeParameter = unsigned int;

    AssertThat<DummyFilter>::isConstructible(With<AreaSizeParameter>());
}

TEST(AreaClosingFilterTest, bigHoleIsntFilled) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = AreaClosingFilter<Image<PixelType>, ImageType>;

    const unsigned int maximumHoleSize = 9;
    const unsigned int imageSize = 6;
    const unsigned int squareSize = 4;

    const unsigned int squareStart = 1;
    const unsigned int squareEnd = squareStart + squareSize - 1;

    FilterType filter(maximumHoleSize);
    ImageType sourceImage(imageSize, imageSize);
    ImageType& expectedImage = sourceImage;

    sourceImage = [] (unsigned int x, unsigned int y) {
        if (x >= squareStart && x <= squareEnd && y >= squareStart
                && y <= squareEnd) {
            return 100;
        } else
            return 199;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}
