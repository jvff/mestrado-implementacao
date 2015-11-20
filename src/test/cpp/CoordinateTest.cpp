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

TEST(CoordinateTest, hasDistanceToMethod) {
    unsigned int firstX = 1390;
    unsigned int firstY = 2342;
    unsigned int secondX = 908;
    unsigned int secondY = 9039;

    float deltaX = firstX - secondX;
    float deltaY = secondY - firstY;
    float expectedDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    const auto first = Coordinate(firstX, firstY);
    const auto second = Coordinate(secondX, secondY);
    auto firstResult = first.distanceTo(second);
    auto secondResult = second.distanceTo(first);

    assertThat(firstResult).isEqualTo(expectedDistance);
    assertThat(secondResult).isEqualTo(expectedDistance);
}

TEST(CoordinateTest, isComparable) {
    unsigned int x = 256;
    unsigned int y = 789;

    const auto first = Coordinate(x, y);
    const auto second = Coordinate(x, y);

    assertThat(first).isEqualTo(first);
    assertThat(first).isEqualTo(second);
    assertThat(second).isEqualTo(second);
}

TEST(CoordinateTest, equalsOperatorConsidersBothCoordinateValues) {
    unsigned int left = 193;
    unsigned int up = 982;
    unsigned int right = 201;
    unsigned int down = 989;

    const auto topLeft = Coordinate(left, up);
    const auto topRight = Coordinate(right, up);
    const auto bottomLeft = Coordinate(left, down);

    assertThat(topLeft).isEqualTo(topLeft);
    assertThat(topLeft).isNotEqualTo(topRight);
    assertThat(topLeft).isNotEqualTo(bottomLeft);

    assertThat(topRight).isNotEqualTo(topLeft);
    assertThat(topRight).isEqualTo(topRight);
    assertThat(topRight).isNotEqualTo(bottomLeft);

    assertThat(bottomLeft).isNotEqualTo(topLeft);
    assertThat(bottomLeft).isNotEqualTo(topRight);
    assertThat(bottomLeft).isEqualTo(bottomLeft);
}

TEST(CoordinateTest, hasIsDifferentThanOperator) {
    unsigned int firstX = 167;
    unsigned int firstY = 12;
    unsigned int secondX = 911;
    unsigned int secondY = 482;

    const auto first = Coordinate(firstX, firstY);
    const auto second = Coordinate(secondX, secondY);

    assertThat(first).isDifferentThan(second);
    assertThat(first).isNotDifferentThan(first);
    assertThat(second).isNotDifferentThan(second);
}

TEST(CoordinateTest, isDifferentThanOperatorConsidersBothCoordinateValues) {
    unsigned int left = 194;
    unsigned int up = 981;
    unsigned int right = 203;
    unsigned int down = 987;

    const auto topLeft = Coordinate(left, up);
    const auto topRight = Coordinate(right, up);
    const auto bottomLeft = Coordinate(left, down);

    assertThat(topLeft).isNotDifferentThan(topLeft);
    assertThat(topLeft).isDifferentThan(topRight);
    assertThat(topLeft).isDifferentThan(bottomLeft);

    assertThat(topRight).isDifferentThan(topLeft);
    assertThat(topRight).isNotDifferentThan(topRight);
    assertThat(topRight).isDifferentThan(bottomLeft);

    assertThat(bottomLeft).isDifferentThan(topLeft);
    assertThat(bottomLeft).isDifferentThan(topRight);
    assertThat(bottomLeft).isNotDifferentThan(bottomLeft);
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
