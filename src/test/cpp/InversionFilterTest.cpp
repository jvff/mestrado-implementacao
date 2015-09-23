#include <gtest/gtest.h>

#include "asserts.hpp"

#include "InversionFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(InversionFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = InversionFilter<Image<DummyType>, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}
