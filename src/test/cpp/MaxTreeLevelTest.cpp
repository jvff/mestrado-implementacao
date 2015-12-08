#include "MaxTreeLevelTest.hpp"

TEST_F(MaxTreeLevelTest, classTemplateExists) {
    AssertThat<DummyMaxTreeLevel>::isClassOrStruct();
}

TEST_F(MaxTreeLevelTest, isConstructibleWithLevelParameter) {
    using LevelParameter = const DummyType&;

    AssertThat<DummyMaxTreeLevel>::isConstructible(With<LevelParameter>());
}

TEST_F(MaxTreeLevelTest, isInitiallyEmpty) {
    assertThat(level.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelTest, isNotEmpyAfterAddingNode) {
    level.addNode();

    assertThat(level.isEmpty()).isEqualTo(false);
}

TEST_F(MaxTreeLevelTest, addNodeReturnsPointerToFirstNode) {
    auto firstNode = level.addNode();

    verifyNode(firstNode, 0u);
}

TEST_F(MaxTreeLevelTest, addNodeReturnsPointerToSecondNode) {
    auto firstNode = level.addNode();
    auto secondNode = level.addNode();

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u);
}

TEST_F(MaxTreeLevelTest, nodesAreRetrievable) {
    level.addNode();
    level.addNode();
    level.addNode();

    auto thirdNode = level.getNode(2u);
    auto firstNode = level.getNode(0u);
    auto secondNode = level.getNode(1u);

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u);
    verifyNode(thirdNode, 2u);
}

TEST_F(MaxTreeLevelTest, retrievedNodesAreTheSameAsNewNodes) {
    auto firstNewNode = level.addNode();
    auto secondNewNode = level.addNode();
    auto thirdNewNode = level.addNode();

    auto thirdNode = level.getNode(2u);
    auto firstNode = level.getNode(0u);
    auto secondNode = level.getNode(1u);

    verifyNode(firstNewNode, 0u);
    verifyNode(secondNewNode, 1u);
    verifyNode(thirdNewNode, 2u);

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u);
    verifyNode(thirdNode, 2u);

    assertThat(firstNode).isEqualTo(firstNewNode);
    assertThat(secondNode).isEqualTo(secondNewNode);
    assertThat(thirdNode).isEqualTo(thirdNewNode);
}
