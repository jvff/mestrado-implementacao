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

TEST(MaxTreeNodeOrderTest, nodeWithSmallerIdComesBeforeNodeWithLargerId) {
    auto level = DummyType{ 83921 };

    const auto nodeWithSmallerId = MaxTreeNode<DummyType>(level, 75199u);
    const auto nodeWithLargerId = MaxTreeNode<DummyType>(level, 75200u);

    assertThat(nodeWithSmallerId).isLessThan(nodeWithLargerId);
    assertThat(nodeWithLargerId).isNotLessThan(nodeWithSmallerId);
}
