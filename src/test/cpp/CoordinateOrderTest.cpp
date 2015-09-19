#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Coordinate.hpp"

#include "AssertionsSpecificForCoordinate.hpp"

TEST(CoordinateOrderTest, isOrderable) {
    unsigned int left = 193;
    unsigned int up = 982;
    unsigned int right = 201;
    unsigned int down = 989;

    const auto topLeft = Coordinate(left, up);
    const auto topRight = Coordinate(right, up);
    const auto bottomLeft = Coordinate(left, down);
    const auto bottomRight = Coordinate(right, down);

    assertThat(topLeft).isEqualTo(topLeft);
    assertThat(topLeft).isBefore(topRight);
    assertThat(topLeft).isBefore(bottomLeft);
    assertThat(topLeft).isBefore(bottomRight);

    assertThat(topRight).isAfter(topLeft);
    assertThat(topRight).isEqualTo(topRight);
    assertThat(topRight).isAfter(bottomLeft);
    assertThat(topRight).isBefore(bottomRight);

    assertThat(bottomLeft).isAfter(topLeft);
    assertThat(bottomLeft).isBefore(topRight);
    assertThat(bottomLeft).isEqualTo(bottomLeft);
    assertThat(bottomLeft).isBefore(bottomRight);

    assertThat(bottomRight).isAfter(topLeft);
    assertThat(bottomRight).isAfter(topRight);
    assertThat(bottomRight).isAfter(bottomLeft);
    assertThat(bottomRight).isEqualTo(bottomRight);
}
