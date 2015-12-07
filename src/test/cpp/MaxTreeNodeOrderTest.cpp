#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeNodeOrderTest, nodeOnLowerLevelComesBeforeNodeOnHigherLevel) {
    const auto nodeOnLowerLevel = MaxTreeNode<DummyType>(DummyType{ 74 }, 0u);
    const auto nodeOnHigherLevel = MaxTreeNode<DummyType>(DummyType{ 75 }, 0u);

    assertThat(nodeOnLowerLevel).isLessThan(nodeOnHigherLevel);
    assertThat(nodeOnHigherLevel).isNotLessThan(nodeOnLowerLevel);
}
