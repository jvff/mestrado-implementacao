#include "MaxTreeNodeComparisonTest.hpp"

TEST_F(MaxTreeNodeComparisonTest, isComparable) {
    auto level = DummyType{ 371 };
    auto id = 85u;

    const auto firstNode = makeNode(level, id);
    const auto secondNode = makeNode(level, id);

    assertThat(firstNode).isEqualTo(secondNode);
    assertThat(secondNode).isEqualTo(firstNode);
}

TEST_F(MaxTreeNodeComparisonTest, nodesWithDifferentLevelsArentEqual) {
    auto id = 85u;

    const auto firstNode = makeNode(DummyType{ 371 }, id);
    const auto secondNode = makeNode(DummyType{ 794 }, id);

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST_F(MaxTreeNodeComparisonTest, nodesWithDifferentIdsArentEqual) {
    auto level = DummyType{ 794 };

    const auto firstNode = makeNode(level, 239u);
    const auto secondNode = makeNode(level, 840u);

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST_F(MaxTreeNodeComparisonTest, nodeWithParentAndNodeWithoutArentEqual) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto nodeWithParent = makeNodeChain(DummyType{ 92 }, 12u, level, id);
    const auto nodeWithoutParent = makeNode(level, id);

    assertThat(nodeWithParent).isNotEqualTo(nodeWithoutParent);
    assertThat(nodeWithoutParent).isNotEqualTo(nodeWithParent);
}

TEST_F(MaxTreeNodeComparisonTest, nodeWithDifferentParentsArentEqual) {
    auto parentLevel = DummyType{ 92 };
    auto parentId = 12u;

    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto firstNode = makeNodeChain(parentLevel, parentId, level, id);
    const auto secondNode = makeNodeChain(parentLevel, parentId, level, id);

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST_F(MaxTreeNodeComparisonTest, nodeWithSameParentAreEqual) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    auto parent = std::make_shared<NodeType>(DummyType{ 92 }, 12u);

    const auto firstNode = makeNode(parent, level, id);
    const auto secondNode = makeNode(parent, level, id);

    assertThat(firstNode).isEqualTo(secondNode);
    assertThat(secondNode).isEqualTo(firstNode);
}

TEST_F(MaxTreeNodeComparisonTest, isComparableToEquivalentNode) {
    auto level = DummyType{ 371 };
    auto id = 85u;

    const auto firstNode = makeNode(level, id);
    const auto secondNode = makeNode(level, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(true);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(true);
}

TEST_F(MaxTreeNodeComparisonTest, nodesWithDifferentLevelsArentEquivalent) {
    auto id = 85u;

    const auto firstNode = makeNode(DummyType{ 371 }, id);
    const auto secondNode = makeNode(DummyType{ 794 }, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST_F(MaxTreeNodeComparisonTest, nodesWithDifferentIdsArentEquivalent) {
    auto level = DummyType{ 794 };

    const auto firstNode = makeNode(level, 239u);
    const auto secondNode = makeNode(level, 840u);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST_F(MaxTreeNodeComparisonTest, nodeWithParentAndNodeWithoutArentEquivalent) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto nodeWithParent = makeNodeChain(DummyType{ 92 }, 12u, level, id);
    const auto nodeWithoutParent = makeNode(level, id);

    assertThat(nodeWithParent.isEquivalentTo(nodeWithoutParent))
        .isEqualTo(false);
    assertThat(nodeWithoutParent.isEquivalentTo(nodeWithParent))
        .isEqualTo(false);
}

TEST_F(MaxTreeNodeComparisonTest, nodeWithDifferentParentsArentEquivalent) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto firstNode = makeNodeChain(DummyType{ 109 }, 60u, level, id);
    const auto secondNode = makeNodeChain(DummyType{ 511 }, 12u, level, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST_F(MaxTreeNodeComparisonTest, nodeWithSameParentAreEquivalent) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    auto parent = std::make_shared<NodeType>(DummyType{ 92 }, 12u);

    const auto firstNode = makeNode(parent, level, id);
    const auto secondNode = makeNode(parent, level, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(true);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(true);
}
