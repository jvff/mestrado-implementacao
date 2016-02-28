#include "MinMaxTreeTest.hpp"

#define TEST_FIXTURE ComparisonTests

SUB_TEST();

TEST_C(isComparable) {
    assertThat(constTree).isEqualTo(constTree);
}

TEST_C(emptyTreesAreEqual) {
    auto emptyTree = DummyMinMaxTreeType();
    const auto& constEmptyTree = emptyTree;

    assertThat(constTree).isEqualTo(constEmptyTree);
    assertThat(constEmptyTree).isEqualTo(constTree);
}

TEST_C(treeWithNodeIsNotEqualToEmptyTree) {
    auto emptyTree = DummyMinMaxTreeType();
    const auto& constEmptyTree = emptyTree;

    tree.addNode(DummyType{ 2918 });

    assertThat(constTree).isNotEqualTo(constEmptyTree);
    assertThat(constEmptyTree).isNotEqualTo(constTree);
}

TEST_C(treesWithTheSameNodeAreEqual) {
    auto otherTree = DummyMinMaxTreeType();
    const auto& constOtherTree = otherTree;

    auto nodeLevelHeight = DummyType{ 7025 };

    tree.addNode(nodeLevelHeight);
    otherTree.addNode(nodeLevelHeight);

    assertThat(constTree).isEqualTo(constOtherTree);
    assertThat(constOtherTree).isEqualTo(constTree);
}

TEST_C(treesWithDifferentAmountOfNodesDiffer) {
    auto otherTree = DummyMinMaxTreeType();
    const auto& constOtherTree = otherTree;

    auto nodeLevelHeight = DummyType{ 7025 };

    tree.addNode(nodeLevelHeight);
    tree.addNode(nodeLevelHeight);
    tree.addNode(nodeLevelHeight);

    otherTree.addNode(nodeLevelHeight);
    otherTree.addNode(nodeLevelHeight);
    otherTree.addNode(nodeLevelHeight);
    otherTree.addNode(nodeLevelHeight);

    assertThat(constTree).isNotEqualTo(constOtherTree);
    assertThat(constOtherTree).isNotEqualTo(constTree);
}

TEST_C(treesWithSameNodesAreEqual) {
    auto otherTree = DummyMinMaxTreeType();
    const auto& constOtherTree = otherTree;

    auto firstLevelHeight = DummyType{ 3078 };
    auto secondLevelHeight = DummyType{ -579 };
    auto thirdLevelHeight = DummyType{ 3801 };

    auto& rootNode = tree.addNode(firstLevelHeight);

    auto& firstNodeOnSecondLevel = tree.addNode(secondLevelHeight);
    auto& secondNodeOnSecondLevel = tree.addNode(secondLevelHeight);

    auto& firstNodeOnThirdLevel = tree.addNode(thirdLevelHeight);
    auto& secondNodeOnThirdLevel = tree.addNode(thirdLevelHeight);
    auto& thirdNodeOnThirdLevel = tree.addNode(thirdLevelHeight);

    tree.setNodeParent(firstNodeOnSecondLevel, rootNode);
    tree.setNodeParent(secondNodeOnSecondLevel, rootNode);

    tree.setNodeParent(firstNodeOnThirdLevel, firstNodeOnSecondLevel);
    tree.setNodeParent(secondNodeOnThirdLevel, firstNodeOnSecondLevel);
    tree.setNodeParent(thirdNodeOnThirdLevel, secondNodeOnSecondLevel);

    auto& otherRootNode = otherTree.addNode(firstLevelHeight);

    auto& otherFirstNodeOnSecondLevel = otherTree.addNode(secondLevelHeight);
    auto& otherSecondNodeOnSecondLevel = otherTree.addNode(secondLevelHeight);

    auto& otherFirstNodeOnThirdLevel = otherTree.addNode(thirdLevelHeight);
    auto& otherSecondNodeOnThirdLevel = otherTree.addNode(thirdLevelHeight);
    auto& otherThirdNodeOnThirdLevel = otherTree.addNode(thirdLevelHeight);

    otherTree.setNodeParent(otherFirstNodeOnSecondLevel, otherRootNode);
    otherTree.setNodeParent(otherSecondNodeOnSecondLevel, otherRootNode);

    otherTree.setNodeParent(otherFirstNodeOnThirdLevel,
            otherFirstNodeOnSecondLevel);
    otherTree.setNodeParent(otherSecondNodeOnThirdLevel,
            otherFirstNodeOnSecondLevel);
    otherTree.setNodeParent(otherThirdNodeOnThirdLevel,
            otherSecondNodeOnSecondLevel);

    assertThat(constTree).isEqualTo(constOtherTree);
    assertThat(constOtherTree).isEqualTo(constTree);
}

TEST_C(treesWithNodesWithDifferentParentsDiffer) {
    auto otherTree = DummyMinMaxTreeType();
    const auto& constOtherTree = otherTree;

    auto firstLevelHeight = DummyType{ 3078 };
    auto secondLevelHeight = DummyType{ -579 };
    auto thirdLevelHeight = DummyType{ 3801 };

    auto& rootNode = tree.addNode(firstLevelHeight);

    auto& firstNodeOnSecondLevel = tree.addNode(secondLevelHeight);
    auto& secondNodeOnSecondLevel = tree.addNode(secondLevelHeight);

    auto& firstNodeOnThirdLevel = tree.addNode(thirdLevelHeight);
    auto& secondNodeOnThirdLevel = tree.addNode(thirdLevelHeight);
    auto& thirdNodeOnThirdLevel = tree.addNode(thirdLevelHeight);

    tree.setNodeParent(firstNodeOnSecondLevel, rootNode);
    tree.setNodeParent(secondNodeOnSecondLevel, rootNode);

    tree.setNodeParent(firstNodeOnThirdLevel, firstNodeOnSecondLevel);
    tree.setNodeParent(thirdNodeOnThirdLevel, secondNodeOnSecondLevel);

    auto& otherRootNode = otherTree.addNode(firstLevelHeight);

    auto& otherFirstNodeOnSecondLevel = otherTree.addNode(secondLevelHeight);
    auto& otherSecondNodeOnSecondLevel = otherTree.addNode(secondLevelHeight);

    auto& otherFirstNodeOnThirdLevel = otherTree.addNode(thirdLevelHeight);
    auto& otherSecondNodeOnThirdLevel = otherTree.addNode(thirdLevelHeight);
    auto& otherThirdNodeOnThirdLevel = otherTree.addNode(thirdLevelHeight);

    otherTree.setNodeParent(otherFirstNodeOnSecondLevel, otherRootNode);
    otherTree.setNodeParent(otherSecondNodeOnSecondLevel, otherRootNode);

    otherTree.setNodeParent(otherFirstNodeOnThirdLevel,
            otherFirstNodeOnSecondLevel);
    otherTree.setNodeParent(otherThirdNodeOnThirdLevel,
            otherSecondNodeOnSecondLevel);

    tree.setNodeParent(secondNodeOnThirdLevel, firstNodeOnSecondLevel);
    otherTree.setNodeParent(otherSecondNodeOnThirdLevel,
            otherSecondNodeOnSecondLevel);

    assertThat(constTree).isNotEqualTo(constOtherTree);
    assertThat(constOtherTree).isNotEqualTo(constTree);
}
