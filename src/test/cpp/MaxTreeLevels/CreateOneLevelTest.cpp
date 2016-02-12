#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(CreateOneLevelTest);

TEST_C(CreateOneLevelTest, createdLevelHasCorrectHeight) {
    auto levelHeight = DummyType{ 14931 };
    auto& level = levels.getOrCreateLevel(levelHeight);

    assertThat(level.getLevel()).isEqualTo(levelHeight);
}

TEST_C(CreateOneLevelTest, createdLevelIsEmpty) {
    auto& level = levels.getOrCreateLevel(DummyType{ 14931 });

    assertThat(level.isEmpty()).isEqualTo(true);
}

TEST_C(CreateOneLevelTest, cantCreateSameLevelTwice) {
    auto levelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(levelHeight);
    auto& retrievedLevel = levels.getOrCreateLevel(levelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_C(CreateOneLevelTest, createdLevelCanBeRetrieved) {
    auto levelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(levelHeight);
    auto& retrievedLevel = levels.getLevel(levelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_C(CreateOneLevelTest, createdLevelCanBeRetrievedThroughConstReference) {
    auto levelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(levelHeight);
    auto& retrievedLevel = constLevels.getLevel(levelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_C(CreateOneLevelTest, isNotEmptyAfterCreatingLevel) {
    levels.getOrCreateLevel(DummyType{ 74931 });

    assertThat(constLevels.isEmpty()).isEqualTo(false);
}

TEST_C(CreateOneLevelTest, hasOneLevelAfterCreatingLevel) {
    levels.getOrCreateLevel(DummyType{ 75042 });

    assertThat(constLevels.numberOfLevels()).isEqualTo(1u);
}

TEST_C(CreateOneLevelTest, hasCreatedLevel) {
    auto levelHeight = 75042;
    auto levelHeightAbove = 75043;
    auto levelHeightBelow = 75040;
    auto negativeLevelHeight = -75042;
    auto negativeLevelHeightBelow = -75043;
    auto negativeLevelHeightAbove = -75040;

    levels.getOrCreateLevel(DummyType{ levelHeight });

    verifyIfHasLevels(levelHeight);

    verifyDoesNotHaveLevels(minimumLevel, negativeLevelHeightBelow,
            negativeLevelHeight, negativeLevelHeightAbove, -345, -3, -2, -1, 0,
            1, 2, 3, 345, levelHeightBelow, levelHeightAbove, maximumLevel);
}

TEST_C(CreateOneLevelTest, firstLevelHeightIsTheSameAsTheCreatedLevelHeight) {
    auto levelHeight = DummyType{ 14936 };

    levels.getOrCreateLevel(levelHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(levelHeight);
}

TEST_C(CreateOneLevelTest, firstLevelIsTheSameAsTheCreatedLevel) {
    auto& createdLevel = levels.getOrCreateLevel(DummyType{ 59783 });
    auto& firstLevel = levels.getFirstLevel();

    assertThat(firstLevel).isAtSameAddressAs(createdLevel);
}
