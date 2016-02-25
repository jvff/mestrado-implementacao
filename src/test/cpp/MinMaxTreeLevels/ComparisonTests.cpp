#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(ComparisonTests);

TEST_C(ComparisonTests, isComparable) {
    assertThat(constLevels).isEqualTo(constLevels);
}

TEST_C(ComparisonTests, emptyLevelsAreTheSame) {
    DummyMinMaxTreeLevels emptyLevels;
    const auto& constEmptyLevels = emptyLevels;

    assertThat(constEmptyLevels).isEqualTo(constLevels);
    assertThat(constLevels).isEqualTo(constEmptyLevels);
}
