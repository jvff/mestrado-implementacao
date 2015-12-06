#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeNodeComparisonTest, isComparable) {
    auto level = DummyType{ 371 };
    auto id = 85u;

    auto firstNode = MaxTreeNode<DummyType>{ level, id };
    auto secondNode = MaxTreeNode<DummyType>{ level, id };

    assertThat(firstNode).isEqualTo(secondNode);
    assertThat(secondNode).isEqualTo(firstNode);
}

TEST(MaxTreeNodeComparisonTest, nodesWithDifferentLevelsArentEqual) {
    auto firstLevel = DummyType{ 371 };
    auto secondLevel = DummyType{ 794 };
    auto id = 85u;

    auto firstNode = MaxTreeNode<DummyType>{ firstLevel, id };
    auto secondNode = MaxTreeNode<DummyType>{ secondLevel, id };

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}
