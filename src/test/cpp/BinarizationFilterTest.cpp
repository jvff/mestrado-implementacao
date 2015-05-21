#include <gtest/gtest.h>

#include "BinarizationFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(BinarizationFilterTest, classIsntAbstract) {
    auto filter = new BinarizationFilter<DummyType, FakeImage<bool> >();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}
