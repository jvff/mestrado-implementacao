#include "MaxTreeLevelsTest.hpp"

TEST_F(MaxTreeLevelsTest, classTemplateExists) {
    AssertThat<DummyMaxTreeLevels>::isClassOrStruct();
}

TEST_F(MaxTreeLevelsTest, isInitiallyEmpty) {
    assertThat(constLevels.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsTest, initiallyHasZeroLevels) {
    assertThat(constLevels.numberOfLevels()).isEqualTo(0u);
}

TEST_F(MaxTreeLevelsTest, initiallHasNoLevels) {
    auto minimumLevel = DummyType{ std::numeric_limits<int>::min() };
    auto maximumLevel = DummyType{ std::numeric_limits<int>::max() };

    assertThat(constLevels.hasLevel(minimumLevel)).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -345 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -3 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -2 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -1 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 0 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 1 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 2 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 3 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 345 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 75042 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(maximumLevel)).isEqualTo(false);
}

TEST_F(MaxTreeLevelsTest, createdLevelIsEmpty) {
    auto levelHeight = DummyType{ 14931 };
    auto& level = levels.getOrCreateLevel(levelHeight);

    assertThat(level.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsTest, isNotEmptyAfterCreatingLevel) {
    auto levelHeight = DummyType{ 74931 };

    levels.getOrCreateLevel(levelHeight);

    assertThat(constLevels.isEmpty()).isEqualTo(false);
}

TEST_F(MaxTreeLevelsTest, hasOneLevelAfterCreatingLevel) {
    auto levelHeight = DummyType{ 75042 };

    levels.getOrCreateLevel(levelHeight);

    assertThat(constLevels.numberOfLevels()).isEqualTo(1u);
}

TEST_F(MaxTreeLevelsTest, hasCreatedLevel) {
    auto levelHeight = DummyType{ 75042 };
    auto levelHeightAbove = DummyType{ 75043 };
    auto levelHeightBelow = DummyType{ 75040 };
    auto negativeLevelHeight = DummyType{ -75042 };
    auto negativeLevelHeightBelow = DummyType{ -75043 };
    auto negativeLevelHeightAbove = DummyType{ -75040 };
    auto minimumLevel = DummyType{ std::numeric_limits<int>::min() };
    auto maximumLevel = DummyType{ std::numeric_limits<int>::max() };

    levels.getOrCreateLevel(levelHeight);

    assertThat(constLevels.hasLevel(levelHeight)).isEqualTo(true);

    assertThat(constLevels.hasLevel(minimumLevel)).isEqualTo(false);
    assertThat(constLevels.hasLevel(negativeLevelHeightBelow)).isEqualTo(false);
    assertThat(constLevels.hasLevel(negativeLevelHeight)).isEqualTo(false);
    assertThat(constLevels.hasLevel(negativeLevelHeightAbove)).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -345 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -3 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -2 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ -1 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 0 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 1 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 2 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 3 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(DummyType{ 345 })).isEqualTo(false);
    assertThat(constLevels.hasLevel(levelHeightBelow)).isEqualTo(false);
    assertThat(constLevels.hasLevel(levelHeightAbove)).isEqualTo(false);
    assertThat(constLevels.hasLevel(maximumLevel)).isEqualTo(false);
}

TEST_F(MaxTreeLevelsTest, firstLevelHeightIsTheSameAsTheCreatedLevelHeight) {
    auto levelHeight = DummyType{ 14936 };

    levels.getOrCreateLevel(levelHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(levelHeight);
}
