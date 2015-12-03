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

    verifyNodeChain(DummyType{ 1 }, 0u);
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
