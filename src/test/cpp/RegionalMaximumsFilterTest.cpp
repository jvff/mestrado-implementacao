#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RegionalMaximumsFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(RegionalMaximumsFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = RegionalMaximumsFilter<DummyType, DummyType, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
