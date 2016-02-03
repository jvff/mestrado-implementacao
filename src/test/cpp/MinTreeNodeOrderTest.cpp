#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MinTreeNodeOrderTest, nodeOnHigherLevelComesBeforeNodeOnLowerLevel) {
    const auto nodeOnHigherLevel = MinTreeNode<DummyType>(DummyType{ 75 }, 0u);
    const auto nodeOnLowerLevel = MinTreeNode<DummyType>(DummyType{ 74 }, 0u);

    assertThat(nodeOnHigherLevel).isLessThan(nodeOnLowerLevel);
    assertThat(nodeOnLowerLevel).isNotLessThan(nodeOnHigherLevel);
}
