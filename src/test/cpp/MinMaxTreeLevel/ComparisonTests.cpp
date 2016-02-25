#include "ComparisonTests.hpp"

using NodeTypes = ::testing::Types<std::less<DummyType>,
        std::greater<DummyType> >;

TYPED_TEST_CASE(MinMaxTreeLevelComparisonTests, NodeTypes);

TEST_C(isComparable) {
    assertThat(constLevel).isEqualTo(constLevel);
}

TEST_C(emptyLevelsWithDifferentHeightsArentEqual) {
    auto differentLevelHeight = DummyType{ 103720 };
    auto emptyDifferentLevel = DummyMinMaxTreeLevel(differentLevelHeight);
    const auto& constEmptyDifferentLevel = emptyDifferentLevel;

    assertThat(constLevel).isNotEqualTo(constEmptyDifferentLevel);
    assertThat(constEmptyDifferentLevel).isNotEqualTo(constLevel);
}

TEST_C(emptyLevelsWithSameHeightAreEqual) {
    auto emptyLevel = DummyMinMaxTreeLevel(levelHeight);
    const auto& constEmptyLevel = emptyLevel;

    assertThat(constLevel).isEqualTo(constEmptyLevel);
    assertThat(constEmptyLevel).isEqualTo(constLevel);
}

TEST_C(populatedLevelsWithTheSameHeightAreEqual) {
    auto otherLevel = DummyMinMaxTreeLevel(levelHeight);
    const auto& constOtherLevel = otherLevel;

    level.addNode();
    level.addNode();
    level.addNode();
    level.addNode();

    otherLevel.addNode();
    otherLevel.addNode();
    otherLevel.addNode();
    otherLevel.addNode();

    assertThat(constLevel).isEqualTo(constOtherLevel);
    assertThat(constOtherLevel).isEqualTo(constLevel);
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

TEST_C(isNotEqualIfLevelHeightsDiffer) {
    auto differentLevelHeight = DummyType{ -318 };
    auto differentLevel = DummyMinMaxTreeLevel(differentLevelHeight);
    const auto& constDifferentLevel = differentLevel;

    level.addNode();
    level.addNode();
    level.addNode();

    differentLevel.addNode();
    differentLevel.addNode();
    differentLevel.addNode();

    assertThat(constLevel).isNotEqualTo(constDifferentLevel);
    assertThat(constDifferentLevel).isNotEqualTo(constLevel);
}

TEST_C(isNotEqualIfLevelHeightsDifferButNodesHasSameHeights) {
    auto differentLevelHeight = DummyType{ -318 };
    auto differentLevel = DummyMinMaxTreeLevel(differentLevelHeight);
    const auto& constDifferentLevel = differentLevel;

    level.addNode();
    level.addNode();

    auto firstNodeToChangeLevel = differentLevel.addNode();
    auto secondNodeToChangeLevel = differentLevel.addNode();

    firstNodeToChangeLevel->setLevel(levelHeight);
    secondNodeToChangeLevel->setLevel(levelHeight);

    assertThat(constLevel).isNotEqualTo(constDifferentLevel);
    assertThat(constDifferentLevel).isNotEqualTo(constLevel);
}
