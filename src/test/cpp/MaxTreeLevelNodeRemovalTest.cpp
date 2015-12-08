#include "MaxTreeLevelNodeRemovalTest.hpp"

TEST_F(MaxTreeLevelNodeRemovalTest, testRemovalOfLastNode) {
    level.addNode();
    auto secondNode = level.addNode();
    level.addNode();

    level.removeNode(2u);

    auto latestNode = level.getLatestNode();

    verifyNode(latestNode, 1u);

    assertThat(latestNode).isEqualTo(secondNode);
}

TEST_F(MaxTreeLevelNodeRemovalTest, testRemovalOfFirstNode) {
    level.addNode();
    level.addNode();
    auto lastNode = level.addNode();

    level.removeNode(0u);

    auto firstNode = level.getNode(0u);
    auto secondNode = level.getNode(1u);
    auto latestNode = level.getLatestNode();

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u);
    verifyNode(latestNode, 1u);

    assertThat(secondNode).isEqualTo(lastNode);
    assertThat(latestNode).isEqualTo(lastNode);
}

TEST_F(MaxTreeLevelNodeRemovalTest, testRemovalOfMiddleNode) {
    level.addNode();
    level.addNode();
    auto lastNode = level.addNode();

    level.removeNode(1u);

    auto firstNode = level.getNode(0u);
    auto secondNode = level.getNode(1u);
    auto latestNode = level.getLatestNode();

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u);
    verifyNode(latestNode, 1u);

    assertThat(secondNode).isEqualTo(lastNode);
    assertThat(latestNode).isEqualTo(lastNode);
}

TEST_F(MaxTreeLevelNodeRemovalTest, testRemovalOfAllNodes) {
    level.addNode();
    level.addNode();

    level.removeNode(1u);
    level.removeNode(0u);

    assertThat(level.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelNodeRemovalTest, removingThenAddingNodeRecreatesIt) {
    auto initialNode = level.addNode();

    level.removeNode(0u);

    auto newNode = level.addNode();

    verifyNode(initialNode, 0u);
    verifyNode(newNode, 0u);

    assertThat(newNode).isNotEqualTo(initialNode);
}

TEST_F(MaxTreeLevelNodeRemovalTest, cantRemoveInexistentNodes) {
    auto firstNode = level.addNode();
    auto secondNode = level.addNode();

    level.removeNode(2u);
    level.removeNode(3u);
    level.removeNode(100u);
    level.removeNode(17000u);

    auto firstReturnedNode = level.getNode(0u);
    auto secondReturnedNode = level.getNode(1u);

    assertThat(firstReturnedNode).isEqualTo(firstNode);
    assertThat(secondReturnedNode).isEqualTo(secondNode);
}
