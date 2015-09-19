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
