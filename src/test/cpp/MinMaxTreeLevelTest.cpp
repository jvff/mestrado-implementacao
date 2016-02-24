#include "MinMaxTreeLevelTest.hpp"

using NodeTypes = ::testing::Types<std::less<DummyType>,
        std::greater<DummyType> >;

TYPED_TEST_CASE(MinMaxTreeLevelTest, NodeTypes);

TEST_C(classTemplateExists) {
    AssertThat<DummyMinMaxTreeLevel>::isClassOrStruct();
}

TEST_C(isConstructibleWithLevelParameter) {
    using LevelParameter = const DummyType&;

    AssertThat<DummyMinMaxTreeLevel>::isConstructible(With<LevelParameter>());
}

TEST_C(levelHeightIsRetrievable) {
    assertThat(constLevel.getLevel()).isEqualTo(levelHeight);
}

TEST_C(isInitiallyEmpty) {
    assertThat(level.isEmpty()).isEqualTo(true);
}

TEST_C(isNotEmpyAfterAddingNode) {
    level.addNode();

    assertThat(level.isEmpty()).isEqualTo(false);
}

TEST_C(addNodeReturnsPointerToFirstNode) {
    auto firstNode = level.addNode();

    verifyNode(firstNode, 0u);
}

TEST_C(addNodeReturnsPointerToSecondNode) {
    auto firstNode = level.addNode();
    auto secondNode = level.addNode();

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u);
}

TEST_C(hasMethodToReplaceParents) {
    auto firstNode = level.addNode();
    auto secondNode = level.addNode();
    auto thirdNode = level.addNode();
    auto fourthNode = level.addNode();

    auto commonParent = makeNode(14u, DummyType{ 100 });
    auto newParent = makeNode(3u, DummyType{ 96 });
    auto differentParent = makeNode(144u, DummyType{ 89 });

    secondNode->setParent(commonParent);
    thirdNode->setParent(differentParent);
    fourthNode->setParent(commonParent);

    level.replaceParents(commonParent, newParent);

    verifyNode(firstNode, 0u);
    verifyNode(secondNode, 1u, newParent);
    verifyNode(thirdNode, 2u, differentParent);
    verifyNode(fourthNode, 3u, newParent);
}

TEST_C(hasMethodToCheckIfNodeExists) {
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

TEST_C(nodesCanBeCollapsed) {
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

TEST_C(isComparable) {
    assertThat(constLevel).isEqualTo(constLevel);
}

TEST_C(isNotEqualIfOnlyOneIsEmpty) {
    auto emptyLevel = DummyMinMaxTreeLevel(levelHeight);
    const auto& constEmptyLevel = emptyLevel;

    level.addNode();

    assertThat(constLevel).isNotEqualTo(constEmptyLevel);
    assertThat(constEmptyLevel).isNotEqualTo(constLevel);
}

TEST_C(isNotEqualIfSizesDiffer) {
    auto smallerLevel = DummyMinMaxTreeLevel(levelHeight);
    const auto& constSmallerLevel = smallerLevel;

    level.addNode();
    level.addNode();
    level.addNode();
    level.addNode();
    level.addNode();

    smallerLevel.addNode();
    smallerLevel.addNode();

    assertThat(constLevel).isNotEqualTo(constSmallerLevel);
    assertThat(constSmallerLevel).isNotEqualTo(constLevel);
}
