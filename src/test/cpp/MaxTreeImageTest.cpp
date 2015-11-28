#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeImage.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MaxTreeImageTest, classTemplateExists) {
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using DummyMaxTreeImageType = MaxTreeImage<InternalImageType>;

    AssertThat<DummyMaxTreeImageType>::isClassOrStruct();
}
