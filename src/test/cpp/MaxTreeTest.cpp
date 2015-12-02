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

TEST(MaxTreeTest, isNotEmptyAfterInsertingNode) {
    MaxTree<DummyType> tree;

    tree.addNode(DummyType{ 0 });

    assertThat(tree.isEmpty()).isEqualTo(false);
}
