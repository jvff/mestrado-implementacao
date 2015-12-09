#include "MaxTreeTest.hpp"

TEST_F(MaxTreeTest, classTemplateExists) {
    AssertThat<DummyMaxTreeType>::isClassOrStruct();
}

TEST_F(MaxTreeTest, isInitiallyEmpty) {
    assertThat(constTree.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeTest, initiallyHasZeroLevels) {
    assertThat(constTree.numberOfLevels()).isEqualTo(0u);
}

TEST_F(MaxTreeTest, isNotEmptyAfterInsertingNode) {
    tree.addNode(DummyType{ 0 });

    assertThat(constTree.isEmpty()).isEqualTo(false);
}

TEST_F(MaxTreeTest, hasOneLevelAfterInsertingNode) {
    tree.addNode(DummyType{ 0 });

    assertThat(constTree.numberOfLevels()).isEqualTo(1u);
}

TEST_F(MaxTreeTest, hasOneLevelAfterInsertingNodesAtSameLevel) {
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });

    assertThat(constTree.numberOfLevels()).isEqualTo(1u);
}

TEST_F(MaxTreeTest, hasTwoLevelsAfterInsertingNodesOnDifferentLevels) {
    tree.addNode(DummyType{ 8 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });

    assertThat(constTree.numberOfLevels()).isEqualTo(2u);
}

TEST_F(MaxTreeTest, nodeCanBeRetrieved) {
    tree.addNode(DummyType{ 1 });

    verifyNodeChain(DummyType{ 1 }, 0u);
}

TEST_F(MaxTreeTest, getNodeReturnsConstReference) {
    auto level = DummyType{ 21890 };
    auto id = 890432u;

    AssertThat<decltype(tree.getNode(level, id))>::isConstReference();
}

TEST_F(MaxTreeTest, getNodeIsConstMethod) {
    assertThat(&MaxTree<DummyType>::getNode).isConstMethod();
}

TEST_F(MaxTreeTest, newNodeDefaultsToNodeOnPreviousLevelAsParent) {
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 2000 });

    verifyNodeChain(
            DummyType{ 2000 }, 0u,
            DummyType{ 1000 }, 0u);
}

TEST_F(MaxTreeTest, newNodeDefaultsToLatestNodeOnPreviousLevelAsParent) {
    tree.addNode(DummyType{ 0 });
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 2000 });

    verifyNodeChain(
            DummyType{ 2000 }, 0u,
            DummyType{ 1000 }, 2u,
            DummyType{ 0 }, 0u);
}

TEST_F(MaxTreeTest, nodeParentCanBeChanged) {
    tree.addNode(DummyType{ 981 });
    tree.addNode(DummyType{ 982 });
    tree.addNode(DummyType{ 983 });

    auto nodeToChange = tree.getNode(DummyType{ 983 }, 0u);
    auto newParent = tree.getNode(DummyType{ 981 }, 0u);

    tree.setNodeParent(nodeToChange, newParent);

    verifyNodeChain(
            DummyType{ 983 }, 0u,
            DummyType{ 981 }, 0u);
}

TEST_F(MaxTreeTest, latestNodeIsRetrievable) {
    tree.addNode(DummyType{ 100 });
    tree.addNode(DummyType{ 101 });
    tree.addNode(DummyType{ 102 });
    tree.addNode(DummyType{ 102 });
    tree.addNode(DummyType{ 102 });
    tree.addNode(DummyType{ 101 });

    verifyNodeChain(tree.getLatestNodeOnLevel(DummyType{ 100 }),
            DummyType{ 100 }, 0u);
    verifyNodeChain(tree.getLatestNodeOnLevel(DummyType{ 101 }),
            DummyType{ 101 }, 1u,
            DummyType{ 100 }, 0u);
    verifyNodeChain(tree.getLatestNodeOnLevel(DummyType{ 102 }),
            DummyType{ 102 }, 2u,
            DummyType{ 101 }, 0u,
            DummyType{ 100 }, 0u);
}

TEST_F(MaxTreeTest, getLatestNodeOnLevelReturnsConstReference) {
    auto level = DummyType{ 21890 };

    AssertThat<decltype(tree.getLatestNodeOnLevel(level))>::isConstReference();
}

TEST_F(MaxTreeTest, getLatestNodeOnLevelIsConstMethod) {
    assertThat(&MaxTree<DummyType>::getLatestNodeOnLevel).isConstMethod();
}

TEST_F(MaxTreeTest, addNodeReturnsConstReference) {
    auto level = DummyType{ 92487 };

    AssertThat<decltype(tree.addNode(level))>::isConstReference();
}

TEST_F(MaxTreeTest, addNodeReturnsNewNode) {
    tree.addNode(DummyType{ 15001 });
    tree.addNode(DummyType{ 15002 });
    tree.addNode(DummyType{ 15003 });
    tree.addNode(DummyType{ 15004 });

    auto& leafNode = tree.addNode(DummyType{ 16000 });

    verifyNodeChain(leafNode,
            DummyType{ 16000 }, 0u,
            DummyType{ 15004 }, 0u,
            DummyType{ 15003 }, 0u,
            DummyType{ 15002 }, 0u,
            DummyType{ 15001 }, 0u);
}

TEST_F(MaxTreeTest, hasLevelReturnsFalseForUnknownLevels) {
    tree.addNode(DummyType{ 15001 });
    tree.addNode(DummyType{ 15002 });
    tree.addNode(DummyType{ 15004 });

    assertThat(tree.hasLevel(DummyType{ 100 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 15000 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 15003 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 15005 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 999999 })).isEqualTo(false);
}

TEST_F(MaxTreeTest, hasLevelReturnsFalseForKnownLevels) {
    tree.addNode(DummyType{ 15001 });
    tree.addNode(DummyType{ 15002 });
    tree.addNode(DummyType{ 15004 });

    assertThat(tree.hasLevel(DummyType{ 15001 })).isEqualTo(true);
    assertThat(tree.hasLevel(DummyType{ 15002 })).isEqualTo(true);
    assertThat(tree.hasLevel(DummyType{ 15004 })).isEqualTo(true);
}
