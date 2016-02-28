#include "MinMaxTreeTest.hpp"

#define TEST_FIXTURE ComparisonTests

SUB_TEST();

TEST_C(isComparable) {
    assertThat(constTree).isEqualTo(constTree);
}
