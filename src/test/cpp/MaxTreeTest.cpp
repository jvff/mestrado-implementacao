#include "MaxTreeTest.hpp"

TEST_F(MaxTreeTest, classTemplateExists) {
    AssertThat<DummyMaxTreeType>::isClassOrStruct();
}

TEST_F(MaxTreeTest, isInitiallyEmpty) {
    assertThat(tree.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeTest, initiallyHasZeroLevels) {
    assertThat(tree.numberOfLevels()).isEqualTo(0u);
}

TEST_F(MaxTreeTest, isNotEmptyAfterInsertingNode) {
    tree.addNode(DummyType{ 0 });

    assertThat(tree.isEmpty()).isEqualTo(false);
}

TEST_F(MaxTreeTest, hasOneLevelAfterInsertingNode) {
    tree.addNode(DummyType{ 0 });

    assertThat(tree.numberOfLevels()).isEqualTo(1u);
}

TEST_F(MaxTreeTest, hasOneLevelAfterInsertingNodesAtSameLevel) {
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });

    assertThat(tree.numberOfLevels()).isEqualTo(1u);
}

TEST_F(MaxTreeTest, isEmptyAfterInsertingThenRemovingNode) {
    tree.addNode(DummyType{ 0 });
    tree.removeNode(DummyType{ 0 }, 0);

    assertThat(tree.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeTest, isNotEmptyAfterInsertingTwoNodesThenRemovingOneNode) {
    tree.addNode(DummyType{ 0 });
    tree.addNode(DummyType{ 0 });
    tree.removeNode(DummyType{ 0 }, 0);

    assertThat(tree.isEmpty()).isEqualTo(false);
}
