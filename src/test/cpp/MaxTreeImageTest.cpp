#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "MaxTreeImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MaxTreeImageTest, classTemplateExists) {
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using DummyMaxTreeImageType = MaxTreeImage<InternalImageType>;

    AssertThat<DummyMaxTreeImageType>::isClassOrStruct();
}

TEST(MaxTreeImageTest, isImage) {
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using DummyMaxTreeImageClass = MaxTreeImage<InternalImageType>;
    using ParentImageClass = Image<PixelType>;

    AssertThat<DummyMaxTreeImageClass>::isSubClass(Of<ParentImageClass>());
}
