#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(RgbImageTest, classTemplateExists) {
    using InternalImageType = FakeImage<DummyType>;
    using DummyRgbImage = RgbImage<InternalImageType>;

    AssertThat<DummyRgbImage>::isClassOrStruct();
}

TEST(RgbImageTest, isSubClassOfImage) {
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageClass = RgbImage<InternalImageType>;
    using ParentImageClass = Image<PixelType>;

    AssertThat<RgbImageClass>::isSubClass(Of<ParentImageClass>());
}
