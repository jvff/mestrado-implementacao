#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaClosingFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AreaClosingFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
