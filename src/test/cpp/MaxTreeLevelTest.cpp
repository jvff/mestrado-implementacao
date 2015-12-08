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

TEST_F(MaxTreeLevelTest, constReferenceToNodeCanBeRetrieved) {
    level.addNode();
    level.addNode();
    level.addNode();

    auto thirdNode = level.getNode(2u);
    auto firstNode = level.getNode(0u);
    auto secondNode = level.getNode(1u);

    auto& secondNodeReference = constLevel.getNodeReference(1u);
    auto& thirdNodeReference = constLevel.getNodeReference(2u);
    auto& firstNodeReference = constLevel.getNodeReference(0u);

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u);
    verifyNode(thirdNode, 2u);

    verifyNode(firstNodeReference, 0u);
    verifyNode(secondNodeReference, 1u);
    verifyNode(thirdNodeReference, 2u);

    assertThat(*firstNode).isAtSameAddressAs(firstNodeReference);
    assertThat(*secondNode).isAtSameAddressAs(secondNodeReference);
    assertThat(*thirdNode).isAtSameAddressAs(thirdNodeReference);
}

TEST_F(MaxTreeLevelTest, getNodeReferenceReturnsConstReference) {
    level.addNode();

    AssertThat<decltype(level.getNodeReference(0u))>::isConstReference();
}

TEST_F(MaxTreeLevelTest, getLatestNodeReturnsLatestNode) {
    level.addNode();
    level.addNode();
    level.addNode();
    level.addNode();

    auto lastNodeAdded = level.addNode();
    auto latestNode = level.getLatestNode();

    verifyNode(lastNodeAdded, 4u);
    verifyNode(latestNode, 4u);

    assertThat(latestNode).isEqualTo(lastNodeAdded);
}

TEST_F(MaxTreeLevelTest, constReferenceToLatestNodeCanBeRetrieved) {
    level.addNode();
    level.addNode();
    level.addNode();

    auto thirdNode = level.getNode(2u);
    auto latestNode = level.getLatestNode();
    auto& latestNodeReference = constLevel.getLatestNodeReference();

    verifyNode(thirdNode, 2u);
    verifyNode(latestNode, 2u);
    verifyNode(latestNodeReference, 2u);

    assertThat(*latestNode).isAtSameAddressAs(*thirdNode);
    assertThat(latestNodeReference).isAtSameAddressAs(*latestNode);
}

TEST_F(MaxTreeLevelTest, getLatestNodeReferenceReturnsConstReference) {
    level.addNode();

    AssertThat<decltype(level.getLatestNodeReference())>::isConstReference();
}

TEST_F(MaxTreeLevelTest, hasMethodToReplaceParents) {
    auto firstNode = level.addNode();
    auto secondNode = level.addNode();
    auto thirdNode = level.addNode();
    auto fourthNode = level.addNode();

    auto commonParent = std::make_shared<NodeType>(DummyType{ 100 }, 14u);
    auto newParent = std::make_shared<NodeType>(DummyType{ 96 }, 3u);
    auto differentParent = std::make_shared<NodeType>(DummyType{ 89 }, 144u);

    secondNode->setParent(commonParent);
    thirdNode->setParent(differentParent);
    fourthNode->setParent(commonParent);

    level.replaceParents(commonParent, newParent);

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u, newParent);
    verifyNode(thirdNode, 2u, differentParent);
    verifyNode(fourthNode, 3u, newParent);
}
