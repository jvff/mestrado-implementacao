#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(ComparisonTests);

TEST_C(ComparisonTests, isComparable) {
    assertThat(constLevels).isEqualTo(constLevels);
}

TEST_C(ComparisonTests, emptyLevelsAreTheSame) {
    DummyMinMaxTreeLevels emptyLevels;
    const auto& constEmptyLevels = emptyLevels;

    assertThat(constEmptyLevels).isEqualTo(constLevels);
    assertThat(constLevels).isEqualTo(constEmptyLevels);
}

TEST_C(ComparisonTests, emptyLevelsDifferFromNonEmptyLevels) {
    DummyMinMaxTreeLevels emptyLevels;
    const auto& constEmptyLevels = emptyLevels;

    levels.getOrCreateLevel(DummyType{ 23 });

    assertThat(constEmptyLevels).isNotEqualTo(constLevels);
    assertThat(constLevels).isNotEqualTo(constEmptyLevels);
}

TEST_C(ComparisonTests, levelsWithSameEmptyLevelsAreEqual) {
    DummyMinMaxTreeLevels otherLevels;
    const auto& constOtherLevels = otherLevels;

    auto firstLevel = DummyType{ 22 };
    auto secondLevel = DummyType{ 12 };
    auto thirdLevel = DummyType{ 96 };

    levels.getOrCreateLevel(firstLevel);
    levels.getOrCreateLevel(secondLevel);
    levels.getOrCreateLevel(thirdLevel);

    otherLevels.getOrCreateLevel(firstLevel);
    otherLevels.getOrCreateLevel(secondLevel);
    otherLevels.getOrCreateLevel(thirdLevel);

    assertThat(constOtherLevels).isEqualTo(constLevels);
    assertThat(constLevels).isEqualTo(constOtherLevels);
}

TEST_C(ComparisonTests, levelsWithDifferentLevelDiffer) {
    DummyMinMaxTreeLevels otherLevels;
    const auto& constOtherLevels = otherLevels;

    auto firstLevel = DummyType{ 22 };
    auto secondLevel = DummyType{ 12 };
    auto thirdLevel = DummyType{ 96 };

    levels.getOrCreateLevel(firstLevel);
    levels.getOrCreateLevel(secondLevel);
    levels.getOrCreateLevel(thirdLevel);

    otherLevels.getOrCreateLevel(firstLevel);
    otherLevels.getOrCreateLevel(secondLevel);
    otherLevels.getOrCreateLevel(thirdLevel);

    otherLevels.getOrCreateLevel(DummyType{ 2038 });

    assertThat(constOtherLevels).isNotEqualTo(constLevels);
    assertThat(constLevels).isNotEqualTo(constOtherLevels);
}

TEST_C(ComparisonTests, levelsWithSameNodesAreEqual) {
    DummyMinMaxTreeLevels otherLevels;
    const auto& constOtherLevels = otherLevels;

    auto firstLevelHeight = DummyType{ 22 };
    auto secondLevelHeight = DummyType{ 12 };

    auto& firstLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& otherFirstLevel = otherLevels.getOrCreateLevel(firstLevelHeight);
    auto& otherSecondLevel = otherLevels.getOrCreateLevel(secondLevelHeight);

    firstLevel.addNode();
    otherFirstLevel.addNode();

    secondLevel.addNode();
    secondLevel.addNode();
    otherSecondLevel.addNode();
    otherSecondLevel.addNode();

    assertThat(constOtherLevels).isEqualTo(constLevels);
    assertThat(constLevels).isEqualTo(constOtherLevels);
}

TEST_C(ComparisonTests, levelsWithDifferentNodesDiffer) {
    DummyMinMaxTreeLevels otherLevels;
    const auto& constOtherLevels = otherLevels;

    auto firstLevelHeight = DummyType{ 22 };
    auto secondLevelHeight = DummyType{ 12 };

    auto& firstLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& otherFirstLevel = otherLevels.getOrCreateLevel(firstLevelHeight);
    auto& otherSecondLevel = otherLevels.getOrCreateLevel(secondLevelHeight);

    firstLevel.addNode();
    otherFirstLevel.addNode();

    secondLevel.addNode();
    secondLevel.addNode();
    otherSecondLevel.addNode();
    otherSecondLevel.addNode();

    otherSecondLevel.addNode();

    assertThat(constOtherLevels).isNotEqualTo(constLevels);
    assertThat(constLevels).isNotEqualTo(constOtherLevels);
}

TEST_C(ComparisonTests, levelsWithNodesWithSameParentsAreEqual) {
    DummyMinMaxTreeLevels otherLevels;
    const auto& constOtherLevels = otherLevels;

    auto firstLevelHeight = DummyType{ 22 };
    auto secondLevelHeight = DummyType{ 12 };

    auto& firstLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& otherFirstLevel = otherLevels.getOrCreateLevel(firstLevelHeight);
    auto& otherSecondLevel = otherLevels.getOrCreateLevel(secondLevelHeight);

    auto rootNode = firstLevel.addNode();
    auto otherRootNode = otherFirstLevel.addNode();

    auto firstLeafNode = secondLevel.addNode();
    auto secondLeafNode = secondLevel.addNode();
    auto otherFirstLeafNode = otherSecondLevel.addNode();
    auto otherSecondLeafNode = otherSecondLevel.addNode();

    firstLeafNode->setParent(rootNode);
    secondLeafNode->setParent(rootNode);

    otherFirstLeafNode->setParent(otherRootNode);
    otherSecondLeafNode->setParent(otherRootNode);

    assertThat(constOtherLevels).isEqualTo(constLevels);
    assertThat(constLevels).isEqualTo(constOtherLevels);
}

TEST_C(ComparisonTests, levelsWithNodesWithDifferentParentsDiffer) {
    DummyMinMaxTreeLevels otherLevels;
    const auto& constOtherLevels = otherLevels;

    auto firstLevelHeight = DummyType{ 22 };
    auto secondLevelHeight = DummyType{ 12 };

    auto& firstLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& otherFirstLevel = otherLevels.getOrCreateLevel(firstLevelHeight);
    auto& otherSecondLevel = otherLevels.getOrCreateLevel(secondLevelHeight);

    firstLevel.addNode();

    auto rootNode = firstLevel.addNode();
    auto otherRootNode = otherFirstLevel.addNode();

    otherFirstLevel.addNode();

    auto firstLeafNode = secondLevel.addNode();
    auto secondLeafNode = secondLevel.addNode();
    auto otherFirstLeafNode = otherSecondLevel.addNode();
    auto otherSecondLeafNode = otherSecondLevel.addNode();

    firstLeafNode->setParent(rootNode);
    secondLeafNode->setParent(rootNode);

    otherFirstLeafNode->setParent(otherRootNode);
    otherSecondLeafNode->setParent(otherRootNode);

    assertThat(constOtherLevels).isNotEqualTo(constLevels);
    assertThat(constLevels).isNotEqualTo(constOtherLevels);
}
