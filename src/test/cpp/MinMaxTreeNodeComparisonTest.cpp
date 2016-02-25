#include "MinMaxTreeNodeComparisonTest.hpp"

using NodeTypes = ::testing::Types<MaxTreeNode<DummyType>,
        MinTreeNode<DummyType> >;

TYPED_TEST_CASE(MaxTreeNodeComparisonTest, NodeTypes);

TEST_C(isComparable) {
    auto level = DummyType{ 371 };
    auto id = 85u;

    const auto firstNode = makeNode(level, id);
    const auto secondNode = makeNode(level, id);

    assertThat(firstNode).isEqualTo(secondNode);
    assertThat(secondNode).isEqualTo(firstNode);
    assertThat(firstNode).isNotDifferentThan(secondNode);
    assertThat(secondNode).isNotDifferentThan(firstNode);
}

TEST_C(nodesWithDifferentLevelsArentEqual) {
    auto id = 85u;

    const auto firstNode = makeNode(DummyType{ 371 }, id);
    const auto secondNode = makeNode(DummyType{ 794 }, id);

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST_C(nodesWithDifferentIdsArentEqual) {
    auto level = DummyType{ 794 };

    const auto firstNode = makeNode(level, 239u);
    const auto secondNode = makeNode(level, 840u);

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST_C(nodeWithParentAndNodeWithoutArentEqual) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto nodeWithParent = makeNodeChain(DummyType{ 92 }, 12u, level, id);
    const auto nodeWithoutParent = makeNode(level, id);

    assertThat(nodeWithParent).isNotEqualTo(nodeWithoutParent);
    assertThat(nodeWithoutParent).isNotEqualTo(nodeWithParent);
}

TEST_C(nodeWithDifferentParentsArentEqual) {
    auto parentLevel = DummyType{ 92 };
    auto parentId = 12u;

    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto firstNode = makeNodeChain(parentLevel, parentId, level, id);
    const auto secondNode = makeNodeChain(parentLevel, parentId, level, id);

    assertThat(firstNode).isNotEqualTo(secondNode);
    assertThat(secondNode).isNotEqualTo(firstNode);
}

TEST_C(nodeWithSameParentAreEqual) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    auto parent = makeNodePointer(DummyType{ 92 }, 12u);

    const auto firstNode = makeNode(parent, level, id);
    const auto secondNode = makeNode(parent, level, id);

    assertThat(firstNode).isEqualTo(secondNode);
    assertThat(secondNode).isEqualTo(firstNode);
}

TEST_C(isComparableToEquivalentNode) {
    auto level = DummyType{ 371 };
    auto id = 85u;

    const auto firstNode = makeNode(level, id);
    const auto secondNode = makeNode(level, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(true);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(true);
}

TEST_C(nodesWithDifferentLevelsArentEquivalent) {
    auto id = 85u;

    const auto firstNode = makeNode(DummyType{ 371 }, id);
    const auto secondNode = makeNode(DummyType{ 794 }, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST_C(nodesWithDifferentIdsArentEquivalent) {
    auto level = DummyType{ 794 };

    const auto firstNode = makeNode(level, 239u);
    const auto secondNode = makeNode(level, 840u);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST_C(nodeWithParentAndNodeWithoutArentEquivalent) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto nodeWithParent = makeNodeChain(DummyType{ 92 }, 12u, level, id);
    const auto nodeWithoutParent = makeNode(level, id);

    assertThat(nodeWithParent.isEquivalentTo(nodeWithoutParent))
        .isEqualTo(false);
    assertThat(nodeWithoutParent.isEquivalentTo(nodeWithParent))
        .isEqualTo(false);
}

TEST_C(nodeWithDifferentParentsArentEquivalent) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto firstNode = makeNodeChain(DummyType{ 109 }, 60u, level, id);
    const auto secondNode = makeNodeChain(DummyType{ 511 }, 12u, level, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST_C(nodeWithSameParentAreEquivalent) {
    auto level = DummyType{ 794 };
    auto id = 279u;

    auto parent = makeNodePointer(DummyType{ 92 }, 12u);

    const auto firstNode = makeNode(parent, level, id);
    const auto secondNode = makeNode(parent, level, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(true);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(true);
}

TEST_C(nodeWithEquivalentParentsAreEquivalent) {
    auto parentLevel = DummyType{ 732 };
    auto parentId = 32u;

    auto level = DummyType{ 794 };
    auto id = 279u;

    const auto firstNode = makeNodeChain(parentLevel, parentId, level, id);
    const auto secondNode = makeNodeChain(parentLevel, parentId, level, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(true);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(true);
}

TEST_C(nodeChainWithDifferentIdsArentEquivalent) {
    auto parentLevel = DummyType{ 732 };
    auto parentId = 32u;

    auto level = DummyType{ 794 };

    const auto firstNode = makeNodeChain(parentLevel, parentId, level, 14u);
    const auto secondNode = makeNodeChain(parentLevel, parentId, level, 15u);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}

TEST_C(nodeChainWithDifferentLevelsArentEquivalent) {
    auto parentLevel = DummyType{ 732 };
    auto parentId = 32u;

    auto id = 1000u;

    const auto firstNode = makeNodeChain(parentLevel, parentId,
            DummyType{ 2044 }, id);
    const auto secondNode = makeNodeChain(parentLevel, parentId,
            DummyType{ 15183 }, id);

    assertThat(firstNode.isEquivalentTo(secondNode)).isEqualTo(false);
    assertThat(secondNode.isEquivalentTo(firstNode)).isEqualTo(false);
}
