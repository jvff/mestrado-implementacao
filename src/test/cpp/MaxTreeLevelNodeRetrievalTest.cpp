#include "MaxTreeLevelNodeRetrievalTest.hpp"

TEST_F(MaxTreeLevelNodeRetrievalTest, cantRetrieveInexistentNode) {
    auto maximumId = std::numeric_limits<unsigned int>::max();

    level.addNode();

    verifyInexistentNodeException([&] () { level.getNode(1u); });
    verifyInexistentNodeException([&] () { level.getNode(2u); });
    verifyInexistentNodeException([&] () { level.getNode(10u); });
    verifyInexistentNodeException([&] () { level.getNode(439u); });
    verifyInexistentNodeException([&] () { level.getNode(7145918u); });
    verifyInexistentNodeException([&] () { level.getNode(maximumId); });
}

TEST_F(MaxTreeLevelNodeRetrievalTest, cantRetrieveReferenceToInexistentNode) {
    auto maximumId = std::numeric_limits<unsigned int>::max();

    level.addNode();

    verifyInexistentNodeException([&] () { level.getNodeReference(1u); });
    verifyInexistentNodeException([&] () { level.getNodeReference(2u); });
    verifyInexistentNodeException([&] () { level.getNodeReference(10u); });
    verifyInexistentNodeException([&] () { level.getNodeReference(439u); });
    verifyInexistentNodeException([&] () { level.getNodeReference(7145918u); });
    verifyInexistentNodeException(
            [&] () { level.getNodeReference(maximumId); });
}

TEST_F(MaxTreeLevelNodeRetrievalTest, nodesAreRetrievable) {
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

TEST_F(MaxTreeLevelNodeRetrievalTest, retrievedNodesAreTheSameAsNewNodes) {
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

TEST_F(MaxTreeLevelNodeRetrievalTest, constReferenceToNodeCanBeRetrieved) {
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

TEST_F(MaxTreeLevelNodeRetrievalTest, getNodeReferenceReturnsConstReference) {
    level.addNode();

    AssertThat<decltype(level.getNodeReference(0u))>::isConstReference();
}

TEST_F(MaxTreeLevelNodeRetrievalTest, getLatestNodeReturnsLatestNode) {
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

TEST_F(MaxTreeLevelNodeRetrievalTest,
        constReferenceToLatestNodeCanBeRetrieved) {
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

TEST_F(MaxTreeLevelNodeRetrievalTest,
        getLatestNodeReferenceReturnsConstReference) {
    level.addNode();

    AssertThat<decltype(level.getLatestNodeReference())>::isConstReference();
}
