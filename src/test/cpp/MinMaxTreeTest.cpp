#include "MinMaxTreeTest.hpp"

using nodeLevelComparatorTypes = ::testing::Types<std::less<DummyType>,
        std::greater<DummyType> >;

TYPED_TEST_CASE(MinMaxTreeTest, nodeLevelComparatorTypes);

TEST_C(classTemplateExists) {
    AssertThat<DummyMinMaxTreeType>::isClassOrStruct();
}

TEST_C(isInitiallyEmpty) {
    assertThat(constTree.isEmpty()).isEqualTo(true);
}

TEST_C(initiallyHasZeroLevels) {
    assertThat(constTree.numberOfLevels()).isEqualTo(0u);
}

TEST_C(isNotEmptyAfterInsertingNode) {
    tree.addNode(DummyType{ 0 });

    assertThat(constTree.isEmpty()).isEqualTo(false);
}

TEST_C(hasOneLevelAfterInsertingNode) {
    tree.addNode(DummyType{ 0 });

    assertThat(constTree.numberOfLevels()).isEqualTo(1u);
}

TEST_C(hasOneLevelAfterInsertingNodesAtSameLevel) {
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });

    assertThat(constTree.numberOfLevels()).isEqualTo(1u);
}

TEST_C(hasTwoLevelsAfterInsertingNodesOnDifferentLevels) {
    tree.addNode(DummyType{ 8 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });
    tree.addNode(DummyType{ 70 });

    assertThat(constTree.numberOfLevels()).isEqualTo(2u);
}

TEST_C(getFirstLevelReturnsExpectedFirstLevel) {
    auto levelHeights = makeLevelHeights({ 2390284, 3000000, 3000001 });
    auto firstLevel = levelHeights[0];

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    assertThat(tree.getFirstLevel()).isEqualTo(firstLevel);
}

TEST_C(nodeCanBeRetrieved) {
    tree.addNode(DummyType{ 1 });

    verifyNodeChain(DummyType{ 1 }, 0u);
}

TEST_C(getNodeReturnsConstReference) {
    auto level = DummyType{ 21890 };
    auto id = 890432u;

    AssertThat<decltype(tree.getNode(level, id))>::isConstReference();
}

TEST_C(getNodeIsConstMethod) {
    assertThat(&DummyMinMaxTreeType::getNode).isConstMethod();
}

TEST_C(newNodeDefaultsToNodeOnPreviousLevelAsParent) {
    auto levelHeights = makeLevelHeights({ 1000, 2000 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);

    verifyNodeChain(
            levelHeights[1], 0u,
            levelHeights[0], 0u);
}

TEST_C(newNodeDefaultsToLatestNodeOnPreviousLevelAsParent) {
    auto levelHeights = makeLevelHeights({ 0, 1000, 2000 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    verifyNodeChain(
            levelHeights[2], 0u,
            levelHeights[1], 2u,
            levelHeights[0], 0u);
}

TEST_C(nodeParentCanBeChanged) {
    auto levelHeights = makeLevelHeights({ 981, 982, 983 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    auto nodeToChange = tree.getNode(levelHeights[2], 0u);
    auto newParent = tree.getNode(levelHeights[0], 0u);

    tree.setNodeParent(nodeToChange, newParent);

    verifyNodeChain(
            levelHeights[2], 0u,
            levelHeights[0], 0u);
}

TEST_C(latestNodeIsRetrievable) {
    auto levelHeights = makeLevelHeights({ 100, 101, 102 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);
    tree.addNode(levelHeights[2]);
    tree.addNode(levelHeights[2]);
    tree.addNode(levelHeights[1]);

    verifyNodeChain(tree.getLatestNodeOnLevel(levelHeights[0]),
            levelHeights[0], 0u);
    verifyNodeChain(tree.getLatestNodeOnLevel(levelHeights[1]),
            levelHeights[1], 1u,
            levelHeights[0], 0u);
    verifyNodeChain(tree.getLatestNodeOnLevel(levelHeights[2]),
            levelHeights[2], 2u,
            levelHeights[1], 0u,
            levelHeights[0], 0u);
}

TEST_C(getLatestNodeOnLevelReturnsConstReference) {
    auto level = DummyType{ 21890 };

    AssertThat<decltype(tree.getLatestNodeOnLevel(level))>::isConstReference();
}

TEST_C(getLatestNodeOnLevelIsConstMethod) {
    assertThat(&DummyMinMaxTreeType::getLatestNodeOnLevel).isConstMethod();
}

TEST_C(addNodeReturnsConstReference) {
    auto level = DummyType{ 92487 };

    AssertThat<decltype(tree.addNode(level))>::isConstReference();
}

TEST_C(addNodeReturnsNewNode) {
    auto levelHeights = makeLevelHeights({ 15001, 15002, 15003, 15004, 16000 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);
    tree.addNode(levelHeights[3]);

    auto& leafNode = tree.addNode(levelHeights[4]);

    verifyNodeChain(leafNode,
            levelHeights[4], 0u,
            levelHeights[3], 0u,
            levelHeights[2], 0u,
            levelHeights[1], 0u,
            levelHeights[0], 0u);
}

TEST_C(hasLevelReturnsFalseForUnknownLevels) {
    auto levelHeights = makeLevelHeights({ 15001, 15002, 15004 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    assertThat(tree.hasLevel(DummyType{ 100 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 15000 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 15003 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 15005 })).isEqualTo(false);
    assertThat(tree.hasLevel(DummyType{ 999999 })).isEqualTo(false);
}

TEST_C(hasLevelReturnsFalseForKnownLevels) {
    auto levelHeights = makeLevelHeights({ 15001, 15002, 15004 });

    tree.addNode(levelHeights[0]);
    tree.addNode(levelHeights[1]);
    tree.addNode(levelHeights[2]);

    assertThat(tree.hasLevel(levelHeights[0])).isEqualTo(true);
    assertThat(tree.hasLevel(levelHeights[1])).isEqualTo(true);
    assertThat(tree.hasLevel(levelHeights[2])).isEqualTo(true);
}
