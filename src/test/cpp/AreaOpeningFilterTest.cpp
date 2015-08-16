#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaOpeningFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AreaOpeningFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
