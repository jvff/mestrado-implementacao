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
