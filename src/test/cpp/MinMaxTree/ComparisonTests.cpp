#include "MinMaxTreeTest.hpp"

#define TEST_FIXTURE ComparisonTests

SUB_TEST();

TEST_C(isComparable) {
    assertThat(constTree).isEqualTo(constTree);
}

TEST_C(emptyTreesAreEqual) {
    auto emptyTree = DummyMinMaxTreeType();
    const auto& constEmptyTree = emptyTree;

    assertThat(constTree).isEqualTo(constEmptyTree);
    assertThat(constEmptyTree).isEqualTo(constTree);
}
