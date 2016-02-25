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
