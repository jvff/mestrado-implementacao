#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(ComparisonTests);

TEST_C(ComparisonTests, isComparable) {
    assertThat(constLevels).isEqualTo(constLevels);
}
