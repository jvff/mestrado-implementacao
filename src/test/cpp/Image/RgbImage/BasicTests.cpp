#include "AllRgbImagePixelTypes.hpp"
#include "RgbImageBasicTests.hpp"

TYPED_TEST_CASE(RgbImageBasicTests, PixelTypes);

TEST_C(classTemplateExists) {
    AssertThat<RgbImageType>::isClassOrStruct();
}

TEST_C(isSubClassOfImage) {
    using ParentImageClass = Image<PixelType>;

    AssertThat<RgbImageType>::isSubClass(Of<ParentImageClass>());
}

TEST_C(isConstructibleWithUnsignedIntImage) {
    using InternalImageParameter = InternalImageType&;

    AssertThat<RgbImageType>::isConstructible(With<InternalImageParameter>());
}

TEST_C(isConstructibleWithUnsignedIntImageAndAlphaFlag) {
    using InternalImageParameter = InternalImageType&;
    using HasAlphaFlag = bool;

    AssertThat<RgbImageType>::isConstructible(
            With<InternalImageParameter, HasAlphaFlag>());
}
