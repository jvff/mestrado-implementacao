#include <gtest/gtest.h>

#include "asserts.hpp"

#include "HminFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(HminFilterTest, classTemplateExists) {
    using DestinationImageType = FakeImage<DummyType>;
    using DummyFilter = HminFilter<Image<DummyType>, DestinationImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
