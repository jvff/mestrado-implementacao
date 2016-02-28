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

TEST_C(treeWithNodeIsNotEqualToEmptyTree) {
    auto emptyTree = DummyMinMaxTreeType();
    const auto& constEmptyTree = emptyTree;

    tree.addNode(DummyType{ 2918 });

    assertThat(constTree).isNotEqualTo(constEmptyTree);
    assertThat(constEmptyTree).isNotEqualTo(constTree);
}
