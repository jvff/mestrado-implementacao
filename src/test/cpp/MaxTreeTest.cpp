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

TEST_F(MaxTreeTest, hasThreeLevelsAfterUsingFourAndEmptyingOne) {
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 8 });
    tree.addNode(DummyType{ 50505 });
    tree.addNode(DummyType{ 8 });
    tree.addNode(DummyType{ 70 });
    tree.removeNode(DummyType{ 8 }, 0u);
    tree.addNode(DummyType{ 1000 });
    tree.removeNode(DummyType{ 8 }, 0u);

    assertThat(constTree.numberOfLevels()).isEqualTo(3u);
}

TEST_F(MaxTreeTest, isEmptyAfterInsertingThenRemovingNode) {
    tree.addNode(DummyType{ 0 });
    tree.removeNode(DummyType{ 0 }, 0);

    assertThat(constTree.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeTest, isNotEmptyAfterInsertingTwoNodesThenRemovingOneNode) {
    tree.addNode(DummyType{ 0 });
    tree.addNode(DummyType{ 0 });
    tree.removeNode(DummyType{ 0 }, 0);

    assertThat(constTree.isEmpty()).isEqualTo(false);
}

TEST_F(MaxTreeTest, nodeCanBeRetrieved) {
    tree.addNode(DummyType{ 1 });

    auto node = tree.getNode(DummyType{ 1 }, 0u);

    verifyNodeChain(node, DummyType{ 1 }, 0u);
}

TEST_F(MaxTreeTest, newNodeDefaultsToNodeOnPreviousLevelAsParent) {
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 2000 });

    auto childNode = tree.getNode(DummyType{ 2000 }, 0u);

    verifyNodeChain(childNode,
            DummyType{ 2000 }, 0u,
            DummyType{ 1000 }, 0u);
}

TEST_F(MaxTreeTest, newNodeDefaultsToLatestNodeOnPreviousLevelAsParent) {
    tree.addNode(DummyType{ 0 });
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 1000 });
    tree.addNode(DummyType{ 2000 });

    auto childNode = tree.getNode(DummyType{ 2000 }, 0u);

    verifyNodeChain(childNode,
            DummyType{ 2000 }, 0u,
            DummyType{ 1000 }, 2u,
            DummyType{ 0 }, 0u);
}

TEST_F(MaxTreeTest, removingNodeUpdatesParentOfChildren) {
    tree.addNode(DummyType{ 20 });
    tree.addNode(DummyType{ 27 });
    tree.addNode(DummyType{ 33 });
    tree.addNode(DummyType{ 30 });
    tree.addNode(DummyType{ 30 });
    tree.removeNode(DummyType{ 27 }, 0u);

    auto firstChild = tree.getNode(DummyType{ 30 }, 0u);
    auto secondChild = tree.getNode(DummyType{ 30 }, 1u);
    auto thirdChild = tree.getNode(DummyType{ 33 }, 0u);

    verifyNodeChain(firstChild,
            DummyType{ 30 }, 0u,
            DummyType{ 20 }, 0u);
    verifyNodeChain(secondChild,
            DummyType{ 30 }, 1u,
            DummyType{ 20 }, 0u);
    verifyNodeChain(thirdChild,
            DummyType{ 33 }, 0u,
            DummyType{ 20 }, 0u);
}

TEST_F(MaxTreeTest, correctNodeIsRemoved) {
    tree.addNode(DummyType{ 1 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 22 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 21 });

    tree.addNode(DummyType{ 10 });
    tree.addNode(DummyType{ 20 });

    tree.removeNode(DummyType{ 10 }, 1u);

    auto middleChild = tree.getNode(DummyType{ 21 }, 0u);

    verifyNodeChain(middleChild,
            DummyType{ 21 }, 0u,
            DummyType{ 1 }, 0u);
}

TEST_F(MaxTreeTest, cantRemoveFromInexistentLevels) {
    tree.addNode(DummyType{ 1 });
    tree.addNode(DummyType{ 3 });
    tree.removeNode(DummyType{ 0 }, 0u);
    tree.removeNode(DummyType{ 2 }, 0u);
    tree.removeNode(DummyType{ 4 }, 0u);

    auto childNode = tree.getNode(DummyType{ 3 }, 0u);

    verifyNodeChain(childNode,
            DummyType{ 3 }, 0u,
            DummyType{ 1 }, 0u);
}

TEST_F(MaxTreeTest, cantRemoveInexistentNode) {
    tree.addNode(DummyType{ 1 });
    tree.addNode(DummyType{ 3 });
    tree.addNode(DummyType{ 3 });
    tree.removeNode(DummyType{ 3 }, 2u);

    auto firstChild = tree.getNode(DummyType{ 3 }, 0u);
    auto secondChild = tree.getNode(DummyType{ 3 }, 1u);

    verifyNodeChain(firstChild,
            DummyType{ 3 }, 0u,
            DummyType{ 1 }, 0u);
    verifyNodeChain(secondChild,
            DummyType{ 3 }, 1u,
            DummyType{ 1 }, 0u);
}
