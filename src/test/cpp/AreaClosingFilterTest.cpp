#include "AreaClosingFilterTest.hpp"

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
    TestData<unsigned char>()
        .setDimensions(6, 6)
        .setMaximumExtremitySize(9)
        .setBackground(199)
        .drawSquare(1, 1, 4, 100);
}
