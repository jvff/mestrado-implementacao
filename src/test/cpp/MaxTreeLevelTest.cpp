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

    assertThat(firstNode->getLevel()).isEqualTo(levelHeight);
    assertThat(firstNode->getId()).isEqualTo(0u);
}

TEST_F(MaxTreeLevelTest, addNodeReturnsPointerToSecondNode) {
    auto firstNode = level.addNode();
    auto secondNode = level.addNode();

    assertThat(firstNode->getLevel()).isEqualTo(levelHeight);
    assertThat(firstNode->getId()).isEqualTo(0u);
    assertThat(secondNode->getLevel()).isEqualTo(levelHeight);
    assertThat(secondNode->getId()).isEqualTo(1u);
}
