#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(RgbImageTest, classTemplateExists) {
    using InternalImageType = FakeImage<unsigned int>;
    using DummyRgbImage = RgbImage<InternalImageType>;

    AssertThat<DummyRgbImage>::isClassOrStruct();
}

TEST(RgbImageTest, isSubClassOfImage) {
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageClass = RgbImage<InternalImageType>;
    using ParentImageClass = Image<PixelType>;

    AssertThat<RgbImageClass>::isSubClass(Of<ParentImageClass>());
}

TEST(RgbImageTest, isConstructibleWithUnsignedIntImage) {
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;
    using IntRgbImageClass = RgbImage<InternalImageType>;
    using IntImageParameter = InternalImageType&;

    AssertThat<IntRgbImageClass>::isConstructible(With<IntImageParameter>());
}
