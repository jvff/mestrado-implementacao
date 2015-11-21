#include "LuminanceFilterTest.hpp"

TEST_F(LuminanceFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(LuminanceFilterTest, isSubClassOfFilter) {
    using ParentFilter = Filter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isSubClass(Of<ParentFilter>());
}

TEST_F(LuminanceFilterTest, rgbSpecializationIsSubClassOfSimpleFilter) {
    using SourcePixelType = unsigned char;
    using InternalImageType = Image<SourcePixelType>;
    using SourceImageType = RgbImage<InternalImageType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = SimpleFilter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isSubClass(Of<ParentFilter>());
}

TEST_F(LuminanceFilterTest, doesntChangeImage) {
    using PixelType = DummyType;
    using SourceImageType = Image<PixelType>;
    using DestinationImageType = SimpleArrayImage<PixelType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;

    unsigned int width = 4;
    unsigned int height = 3;

    DummyFilter filter;
    SimpleArrayImage<PixelType> image(width, height);
    const Image<PixelType>& sourceImage = image;

    image = [=] (unsigned int x, unsigned int y) -> DummyType {
        return DummyType{ (int)(x + y * width) };
    };

    auto resultingImage = filter.apply(image);

    assertThat(resultingImage).isEqualTo(sourceImage);
}
