#include "AreaOpeningFilterTest.hpp"
#include "AreaOpeningTests.hpp"

TEST(AreaOpeningFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AreaOpeningFilter<Image<DummyType>, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(AreaOpeningFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = AreaOpeningFilter<SourceImageType, DestinationImageType>;
    using SuperClass = Filter<SourceImageType, DestinationImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(AreaOpeningFilterTest, isConstructibleWithParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = AreaOpeningFilter<SourceImageType,
            DestinationImageType>;
    using AreaSizeParameter = unsigned int;

    AssertThat<DummyFilter>::isConstructible(With<AreaSizeParameter>());
}

TEST(AreaOpeningFilterTest, bigPlateauIsntCleared) {
    using PixelType = unsigned char;
    using ImageType = SimpleArrayImage<PixelType>;
    using FilterType = AreaOpeningFilter<Image<PixelType>, ImageType>;

    const unsigned int maximumPeakSize = 9;
    const unsigned int imageSize = 6;
    const unsigned int squareSize = 4;

    const unsigned int squareStart = 1;
    const unsigned int squareEnd = squareStart + squareSize - 1;

    FilterType filter(maximumPeakSize);
    ImageType sourceImage(imageSize, imageSize);
    ImageType& expectedImage = sourceImage;

    sourceImage = [] (unsigned int x, unsigned int y) {
        if (x >= squareStart && x <= squareEnd && y >= squareStart
                && y <= squareEnd) {
            return 167;
        } else
            return 102;
    };

    auto result = filter.apply(sourceImage);

    assertThat(result).isEqualTo(expectedImage);
}

INSTANTIATE_TYPED_TEST_CASE_P(AreaOpeningFilterTest, AreaOpeningTests,
        TestData<unsigned char>);
