#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Coordinate.hpp"

TEST(CoordinateTest, structExists) {
    AssertThat<Coordinate>::isClassOrStruct();
}

TEST(CoordinateTest, hasValueMembers) {
    unsigned int x = 1;
    unsigned int y = 2;

    Coordinate coordinate = { x, y };

    assertThat(coordinate.x).isEqualTo(x);
    assertThat(coordinate.y).isEqualTo(y);
}

TEST(CoordinateTest, hasValueConstructor) {
    unsigned int x = 100;
    unsigned int y = 50;

    auto coordinate = Coordinate(x, y);

    assertThat(coordinate.x).isEqualTo(x);
    assertThat(coordinate.y).isEqualTo(y);
}
