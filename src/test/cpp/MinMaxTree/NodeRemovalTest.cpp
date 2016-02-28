#include "MinMaxTreeTest.hpp"

#define TEST_FIXTURE NodeRemovalTest

SUB_TEST();

TEST_C(hasThreeLevelsAfterUsingFourAndEmptyingOne) {
    tree.addNode(DummyType{ 8 });
    tree.addNode(DummyType{ 8 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 50505 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 8 });
    tree.removeNode(DummyType{ 70 }, 0u);
    tree.addNode(DummyType{ 1000 });
    tree.removeNode(DummyType{ 70 }, 0u);

    assertThat(constTree.numberOfLevels()).isEqualTo(3u);
}

TEST_C(isEmptyAfterInsertingThenRemovingNode) {
    tree.addNode(DummyType{ 0 });
    tree.removeNode(DummyType{ 0 }, 0);

    assertThat(constTree.isEmpty()).isEqualTo(true);
}

TEST_C(isNotEmptyAfterInsertingTwoNodesThenRemovingOneNode) {
    auto levelHeights = makeLevelHeights({ 0, 1 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.removeNode(levelHeights[1], 0);

    assertThat(constTree.isEmpty()).isEqualTo(false);
}

TEST_C(removingNodeUpdatesParentOfChildren) {
    auto levelHeights = makeLevelHeights({ 20, 27, 30, 33 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[3]);
    tree.addNode(levelHeights[2]);
    tree.addNode(levelHeights[2]);
    tree.removeNode(levelHeights[1], 0u);

    verifyNodeChain(
            levelHeights[2], 0u,
            levelHeights[0], 0u);
    verifyNodeChain(
            levelHeights[2], 1u,
            levelHeights[0], 0u);
    verifyNodeChain(
            levelHeights[3], 0u,
            levelHeights[0], 0u);
}

TEST_C(correctNodeIsRemoved) {
    auto levelHeights = makeLevelHeights({ 1, 10, 20, 21, 22 });

    tree.addNode(levelHeights[0]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[4]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[3]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    tree.removeNode(levelHeights[1], 1u);

    verifyNodeChain(
            levelHeights[3], 0u,
            levelHeights[0], 0u);
}

TEST_C(cantRemoveFromInexistentLevels) {
    auto levelHeights = makeLevelHeights({ 0, 1, 2, 3, 4 });

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[3]);
    tree.removeNode(levelHeights[0], 0u);
    tree.removeNode(levelHeights[2], 0u);
    tree.removeNode(levelHeights[4], 0u);

    verifyNodeChain(
            levelHeights[3], 0u,
            levelHeights[1], 0u);
}

TEST_C(cantRemoveInexistentNode) {
    auto levelHeights = makeLevelHeights({ 1, 3 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[1]);
    tree.removeNode(levelHeights[1], 2u);

    verifyNodeChain(
            levelHeights[1], 0u,
            levelHeights[0], 0u);
    verifyNodeChain(
            levelHeights[1], 1u,
            levelHeights[0], 0u);
}

TEST_C(nodeIdsAreUpdatedAfterRemoval) {
    auto levelHeights = makeLevelHeights({ 1, 10, 20, 30, 40, 50 });

    tree.addNode(levelHeights[0]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[5]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[4]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[3]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    tree.removeNode(levelHeights[1], 1u);

    verifyNodeChain(
            levelHeights[5], 0u,
            levelHeights[1], 0u,
            levelHeights[0], 0u);
    verifyNodeChain(
            levelHeights[4], 0u,
            levelHeights[0], 0u);
    verifyNodeChain(
            levelHeights[3], 0u,
            levelHeights[1], 1u,
            levelHeights[0], 0u);
    verifyNodeChain(
            levelHeights[2], 0u,
            levelHeights[1], 2u,
            levelHeights[0], 0u);
}

TEST_C(rootNodeRemovalMergesNextLevel) {
    auto levelHeights = makeLevelHeights({ 10, 20, 30, 31 });

    tree.addNode(levelHeights[0]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[3]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    tree.removeNode(levelHeights[0], 0);

    verifyNodeChain(
            levelHeights[3], 0u,
            levelHeights[1], 0u);
    verifyNodeChain(
            levelHeights[2], 0u,
            levelHeights[1], 0u);
    verifyNodeChain(
            levelHeights[2], 1u,
            levelHeights[1], 0u);
}
