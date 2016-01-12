#include "MaxTreeLevelTest.hpp"

TEST_F(MaxTreeLevelTest, classTemplateExists) {
    AssertThat<DummyMaxTreeLevel>::isClassOrStruct();
}

TEST_F(MaxTreeLevelTest, isConstructibleWithLevelParameter) {
    using LevelParameter = const DummyType&;

    AssertThat<DummyMaxTreeLevel>::isConstructible(With<LevelParameter>());
}

TEST_F(MaxTreeLevelTest, levelHeightIsRetrievable) {
    assertThat(constLevel.getLevel()).isEqualTo(levelHeight);
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

TEST_F(MaxTreeLevelTest, hasMethodToCheckIfNodeExists) {
    auto maximumId = std::numeric_limits<unsigned int>::max();

    level.addNode();
    level.addNode();

    assertThat(constLevel.hasNode(0u)).isEqualTo(true);
    assertThat(constLevel.hasNode(1u)).isEqualTo(true);
    assertThat(constLevel.hasNode(2u)).isEqualTo(false);
    assertThat(constLevel.hasNode(100u)).isEqualTo(false);
    assertThat(constLevel.hasNode(17000u)).isEqualTo(false);
    assertThat(constLevel.hasNode(8000000u)).isEqualTo(false);
    assertThat(constLevel.hasNode(maximumId)).isEqualTo(false);
}

TEST_F(MaxTreeLevelTest, nodesCanBeCollapsed) {
    auto firstNode = level.addNode();
    auto secondNode = level.addNode();
    auto thirdNode = level.addNode();
    auto fourthNode = level.addNode();

    auto result = level.collapseNodes();
    auto remainingNode = level.getNode(0u);

    assertThat(constLevel.hasNode(0u)).isEqualTo(true);
    assertThat(constLevel.hasNode(1u)).isEqualTo(false);
    assertThat(constLevel.hasNode(2u)).isEqualTo(false);
    assertThat(constLevel.hasNode(3u)).isEqualTo(false);

    assertThat(result[0]).isEqualTo(secondNode);
    assertThat(result[1]).isEqualTo(thirdNode);
    assertThat(result[2]).isEqualTo(fourthNode);

    assertThat(remainingNode).isEqualTo(firstNode);
}
