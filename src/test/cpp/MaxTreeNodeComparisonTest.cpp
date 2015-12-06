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

TEST(MaxTreeNodeComparisonTest, nodesWithDifferentIdsArentEqual) {
    auto level = DummyType{ 794 };
    auto firstId = 239u;
    auto secondId = 840u;

    auto firstNode = MaxTreeNode<DummyType>{ level, firstId };
    auto secondNode = MaxTreeNode<DummyType>{ level, secondId };

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST(MaxTreeNodeComparisonTest, nodeWithParentAndNodeWithoutArentEqual) {
    auto parentLevel = DummyType{ 92 };
    auto parentId = 12u;

    auto level = DummyType{ 794 };
    auto id = 279u;

    auto parent = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);
    auto firstNode = MaxTreeNode<DummyType>{ parent, level, id };
    auto secondNode = MaxTreeNode<DummyType>{ level, id };

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}
