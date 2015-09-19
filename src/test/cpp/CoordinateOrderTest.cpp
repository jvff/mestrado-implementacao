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

TEST(CoordinateOrderTest, hasAscendingOrderComparator) {
    unsigned int left = 193;
    unsigned int up = 982;
    unsigned int right = 201;
    unsigned int down = 989;

    const auto topLeft = Coordinate(left, up);
    const auto topRight = Coordinate(right, up);
    const auto bottomLeft = Coordinate(left, down);
    const auto bottomRight = Coordinate(right, down);

    const auto compare = Coordinate::AscendingComparator();

    assertThat(compare(topLeft, topLeft)).isEqualTo(false);
    assertThat(compare(topLeft, topRight)).isEqualTo(true);
    assertThat(compare(topLeft, bottomLeft)).isEqualTo(true);
    assertThat(compare(topLeft, bottomRight)).isEqualTo(true);

    assertThat(compare(topRight, topLeft)).isEqualTo(false);
    assertThat(compare(topRight, topRight)).isEqualTo(false);
    assertThat(compare(topRight, bottomLeft)).isEqualTo(false);
    assertThat(compare(topRight, bottomRight)).isEqualTo(true);

    assertThat(compare(bottomLeft, topLeft)).isEqualTo(false);
    assertThat(compare(bottomLeft, topRight)).isEqualTo(true);
    assertThat(compare(bottomLeft, bottomLeft)).isEqualTo(false);
    assertThat(compare(bottomLeft, bottomRight)).isEqualTo(true);

    assertThat(compare(bottomRight, topLeft)).isEqualTo(false);
    assertThat(compare(bottomRight, topRight)).isEqualTo(false);
    assertThat(compare(bottomRight, bottomLeft)).isEqualTo(false);
    assertThat(compare(bottomRight, bottomRight)).isEqualTo(false);
}
