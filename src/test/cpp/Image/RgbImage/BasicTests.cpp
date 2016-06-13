#include "AllRgbImagePixelTypes.hpp"
#include "RgbImageBasicTests.hpp"

TYPED_TEST_CASE(RgbImageBasicTests, PixelTypes);

TEST_C(classTemplateExists) {
    using RgbImageType = typename TestFixture::RgbImageType;

    AssertThat<RgbImageType>::isClassOrStruct();
}

TEST_C(isSubClassOfImage) {
    using PixelType = typename TestFixture::PixelType;
    using RgbImageClass = typename TestFixture::RgbImageType;
    using ParentImageClass = Image<PixelType>;

    AssertThat<RgbImageClass>::isSubClass(Of<ParentImageClass>());
}

TEST_C(isConstructibleWithUnsignedIntImage) {
    using InternalImageType = typename TestFixture::InternalImageType;
    using IntRgbImageClass = typename TestFixture::RgbImageType;
    using IntImageParameter = InternalImageType&;

    AssertThat<IntRgbImageClass>::isConstructible(With<IntImageParameter>());
}

TEST_C(isConstructibleWithUnsignedIntImageAndAlphaFlag) {
    using InternalImageType = typename TestFixture::InternalImageType;
    using IntRgbImageClass = typename TestFixture::RgbImageType;
    using IntImageParameter = InternalImageType&;
    using HasAlphaFlag = bool;

    AssertThat<IntRgbImageClass>::isConstructible(
            With<IntImageParameter, HasAlphaFlag>());
}
