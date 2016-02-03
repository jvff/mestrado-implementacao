#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MinTreeNodeOrderTest, nodeOnHigherLevelComesBeforeNodeOnLowerLevel) {
    const auto nodeOnHigherLevel = MinTreeNode<DummyType>(DummyType{ 75 }, 0u);
    const auto nodeOnLowerLevel = MinTreeNode<DummyType>(DummyType{ 74 }, 0u);

    assertThat(nodeOnHigherLevel).isLessThan(nodeOnLowerLevel);
    assertThat(nodeOnLowerLevel).isNotLessThan(nodeOnHigherLevel);

    assertThat(nodeOnLowerLevel).isGreaterThan(nodeOnHigherLevel);
    assertThat(nodeOnHigherLevel).isNotGreaterThan(nodeOnLowerLevel);
}

TEST(MinTreeNodeOrderTest, nodeWithSmallerIdComesBeforeNodeWithLargerId) {
    auto level = DummyType{ 83921 };

    const auto nodeWithSmallerId = MinTreeNode<DummyType>(level, 75199u);
    const auto nodeWithLargerId = MinTreeNode<DummyType>(level, 75200u);

    assertThat(nodeWithSmallerId).isLessThan(nodeWithLargerId);
    assertThat(nodeWithLargerId).isNotLessThan(nodeWithSmallerId);

    assertThat(nodeWithLargerId).isGreaterThan(nodeWithSmallerId);
    assertThat(nodeWithSmallerId).isNotGreaterThan(nodeWithLargerId);
}
