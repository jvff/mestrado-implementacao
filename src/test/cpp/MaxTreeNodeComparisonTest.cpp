#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MaxTreeNodeComparisonTest, isComparable) {
    auto level = DummyType{ 371 };
    auto id = 85u;

    const auto firstNode = MaxTreeNode<DummyType>{ level, id };
    const auto secondNode = MaxTreeNode<DummyType>{ level, id };

    assertThat(firstNode).isEqualTo(secondNode);
    assertThat(secondNode).isEqualTo(firstNode);
}

TEST(MaxTreeNodeComparisonTest, nodesWithDifferentLevelsArentEqual) {
    auto firstLevel = DummyType{ 371 };
    auto secondLevel = DummyType{ 794 };
    auto id = 85u;

    const auto firstNode = MaxTreeNode<DummyType>{ firstLevel, id };
    const auto secondNode = MaxTreeNode<DummyType>{ secondLevel, id };

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST(MaxTreeNodeComparisonTest, nodesWithDifferentIdsArentEqual) {
    auto level = DummyType{ 794 };
    auto firstId = 239u;
    auto secondId = 840u;

    const auto firstNode = MaxTreeNode<DummyType>{ level, firstId };
    const auto secondNode = MaxTreeNode<DummyType>{ level, secondId };

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
    const auto firstNode = MaxTreeNode<DummyType>{ parent, level, id };
    const auto secondNode = MaxTreeNode<DummyType>{ level, id };

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST(MaxTreeNodeComparisonTest, nodeWithDifferentParentsArentEqual) {
    auto parentLevel = DummyType{ 92 };
    auto parentId = 12u;

    auto level = DummyType{ 794 };
    auto id = 279u;

    auto firstParent = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);
    auto secondParent = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);

    const auto firstNode = MaxTreeNode<DummyType>{ firstParent, level, id };
    const auto secondNode = MaxTreeNode<DummyType>{ secondParent, level, id };

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST(MaxTreeNodeComparisonTest, nodeWithSameParentAreEqual) {
    auto parentLevel = DummyType{ 92 };
    auto parentId = 12u;

    auto level = DummyType{ 794 };
    auto id = 279u;

    auto parent = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);

    const auto firstNode = MaxTreeNode<DummyType>{ parent, level, id };
    const auto secondNode = MaxTreeNode<DummyType>{ parent, level, id };

    assertThat(firstNode).isEqualTo(secondNode);
    assertThat(secondNode).isEqualTo(firstNode);
}

TEST(MaxTreeNodeComparisonTest, isComparableToEquivalentNode) {
    auto level = DummyType{ 371 };
    auto id = 85u;

    const auto firstNode = MaxTreeNode<DummyType>{ level, id };
    const auto secondNode = MaxTreeNode<DummyType>{ level, id };

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(true);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(true);
}

TEST(MaxTreeNodeComparisonTest, nodesWithDifferentLevelsArentEquivalent) {
    auto firstLevel = DummyType{ 371 };
    auto secondLevel = DummyType{ 794 };
    auto id = 85u;

    const auto firstNode = MaxTreeNode<DummyType>{ firstLevel, id };
    const auto secondNode = MaxTreeNode<DummyType>{ secondLevel, id };

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST(MaxTreeNodeComparisonTest, nodesWithDifferentIdsArentEquivalent) {
    auto level = DummyType{ 794 };
    auto firstId = 239u;
    auto secondId = 840u;

    const auto firstNode = MaxTreeNode<DummyType>{ level, firstId };
    const auto secondNode = MaxTreeNode<DummyType>{ level, secondId };

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST(MaxTreeNodeComparisonTest, nodeWithParentAndNodeWithoutArentEquivalent) {
    auto parentLevel = DummyType{ 92 };
    auto parentId = 12u;

    auto level = DummyType{ 794 };
    auto id = 279u;

    auto parent = std::make_shared<MaxTreeNode<DummyType> >(parentLevel,
            parentId);
    const auto firstNode = MaxTreeNode<DummyType>{ parent, level, id };
    const auto secondNode = MaxTreeNode<DummyType>{ level, id };

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}
