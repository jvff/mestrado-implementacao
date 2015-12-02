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
