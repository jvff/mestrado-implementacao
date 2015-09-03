#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Coordinate.hpp"

TEST(CoordinateTest, structExists) {
    AssertThat<Coordinate>::isClassOrStruct();
}
