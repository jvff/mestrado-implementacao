#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTree.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeTest, classTemplateExists) {
    using DummyMaxTreeType = MaxTree<DummyType>;

    AssertThat<DummyMaxTreeType>::isClassOrStruct();
}

TEST(MaxTreeTest, isInitiallyEmpty) {
    MaxTree<DummyType> tree;

    assertThat(tree.isEmpty()).isEqualTo(true);
}

TEST(MaxTreeTest, initiallyHasZeroLevels) {
    MaxTree<DummyType> tree;

    assertThat(tree.numberOfLevels()).isEqualTo(0u);
}

TEST(MaxTreeTest, isNotEmptyAfterInsertingNode) {
    MaxTree<DummyType> tree;

    tree.addNode(DummyType{ 0 });

    assertThat(tree.isEmpty()).isEqualTo(false);
}

TEST(MaxTreeTest, isEmptyAfterInsertingThenRemovingNode) {
    MaxTree<DummyType> tree;

    tree.addNode(DummyType{ 0 });
    tree.removeNode(DummyType{ 0 }, 0);

    assertThat(tree.isEmpty()).isEqualTo(true);
}

TEST(MaxTreeTest, isNotEmptyAfterInsertingTwoNodesThenRemovingOneNode) {
    MaxTree<DummyType> tree;

    tree.addNode(DummyType{ 0 });
    tree.addNode(DummyType{ 0 });
    tree.removeNode(DummyType{ 0 }, 0);

    assertThat(tree.isEmpty()).isEqualTo(false);
}
