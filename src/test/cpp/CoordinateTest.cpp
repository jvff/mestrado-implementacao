#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Coordinate.hpp"

TEST(CoordinateTest, structExists) {
    AssertThat<Coordinate>::isClassOrStruct();
}

TEST(CoordinateTest, hasDefaultConstructor) {
    AssertThat<Coordinate>::isConstructible(WithoutParameters());
}

TEST(CoordinateTest, defaultConstructorIsConstExpression) {
    unsigned int initialX = 0;
    unsigned int initialY = 0;

    constexpr Coordinate coordinate;

    assertThat(coordinate.x).isEqualTo(initialX);
    assertThat(coordinate.y).isEqualTo(initialY);
}

TEST(CoordinateTest, hasValueMembers) {
    unsigned int x = 1;
    unsigned int y = 2;

    Coordinate coordinate = { x, y };

    assertThat(coordinate.x).isEqualTo(x);
    assertThat(coordinate.y).isEqualTo(y);
}

TEST(CoordinateTest, hasValueConstructor) {
    constexpr unsigned int x = 100;
    constexpr unsigned int y = 50;

    constexpr auto coordinate = Coordinate(x, y);

    assertThat(coordinate.x).isEqualTo(x);
    assertThat(coordinate.y).isEqualTo(y);
}

TEST(CoordinateTest, hasAdditionOperator) {
    unsigned int firstX = 390;
    unsigned int firstY = 342;
    unsigned int secondX = 908;
    unsigned int secondY = 939;

    const auto first = Coordinate(firstX, firstY);
    const auto second = Coordinate(secondX, secondY);
    auto result = first + second;

    assertThat(result.x).isEqualTo(firstX + secondX);
    assertThat(result.y).isEqualTo(firstY + secondY);
}

TEST(CoordinateTest, hasLessThanOperator) {
    unsigned int firstX = 193;
    unsigned int firstY = 982;
    unsigned int secondX = 201;
    unsigned int secondY = 989;

    const auto first = Coordinate(firstX, firstY);
    const auto second = Coordinate(secondX, secondY);

    assertThat(first).isLessThan(second);
    assertThat(second).isNotLessThan(first);
    assertThat(first).isNotLessThan(first);
    assertThat(second).isNotLessThan(second);
}

TEST(CoordinateTest, lessThanOperatorConsidersBothCoordinateValues) {
    unsigned int left = 193;
    unsigned int up = 982;
    unsigned int right = 201;
    unsigned int down = 989;

    const auto topLeft = Coordinate(left, up);
    const auto topRight = Coordinate(right, up);
    const auto bottomLeft = Coordinate(left, down);
    const auto bottomRight = Coordinate(right, down);

    assertThat(topLeft).isLessThan(bottomRight);
    assertThat(topLeft).isNotLessThan(topLeft);
    assertThat(topLeft).isNotLessThan(topRight);
    assertThat(topLeft).isNotLessThan(bottomLeft);

    assertThat(topRight).isNotLessThan(topLeft);
    assertThat(topRight).isNotLessThan(topRight);
    assertThat(topRight).isNotLessThan(bottomLeft);
    assertThat(topRight).isNotLessThan(bottomRight);

    assertThat(bottomLeft).isNotLessThan(topLeft);
    assertThat(bottomLeft).isNotLessThan(topRight);
    assertThat(bottomLeft).isNotLessThan(bottomLeft);
    assertThat(bottomLeft).isNotLessThan(bottomRight);

    assertThat(bottomRight).isNotLessThan(topLeft);
    assertThat(bottomRight).isNotLessThan(topRight);
    assertThat(bottomRight).isNotLessThan(bottomLeft);
    assertThat(bottomRight).isNotLessThan(bottomRight);
}
