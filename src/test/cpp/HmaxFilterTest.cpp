#include <gtest/gtest.h>

#include "asserts.hpp"

#include "HmaxFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(HmaxFilterTest, classTemplateExists) {
    using DestinationImageType = FakeImage<DummyType>;
    using DummyFilter = HmaxFilter<Image<DummyType>, DestinationImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
