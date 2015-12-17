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
    auto minimumLevel = std::numeric_limits<int>::min();
    auto maximumLevel = std::numeric_limits<int>::max();

    verifyDoesNotHaveLevels(minimumLevel, -345, -3, -2, -1, 0, 1, 2, 3, 345,
            75042, maximumLevel);
}

TEST_F(MaxTreeLevelsTest, createdLevelHasCorrectHeight) {
    auto levelHeight = DummyType{ 14931 };
    auto& level = levels.getOrCreateLevel(levelHeight);

    assertThat(level.getLevel()).isEqualTo(levelHeight);
}

TEST_F(MaxTreeLevelsTest, createdLevelIsEmpty) {
    auto levelHeight = DummyType{ 14931 };
    auto& level = levels.getOrCreateLevel(levelHeight);

    assertThat(level.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsTest, cantCreateSameLevelTwice) {
    auto levelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(levelHeight);
    auto& retrievedLevel = levels.getOrCreateLevel(levelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsTest, createdLevelCanBeRetrieved) {
    auto levelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(levelHeight);
    auto& retrievedLevel = levels.getLevel(levelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsTest, createdLevelCanBeRetrievedThroughConstReference) {
    auto levelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(levelHeight);
    auto& retrievedLevel = constLevels.getLevel(levelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsTest, levelsCanBeRetrievedAsConstOrNot) {
    auto levelHeight = DummyType{ 12 };

    AssertThat<decltype(constLevels.getLevel(levelHeight))>::isConstReference();
    AssertThat<decltype(levels.getLevel(levelHeight))>::isNonConstReference();
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
    auto levelHeight = 75042;
    auto levelHeightAbove = 75043;
    auto levelHeightBelow = 75040;
    auto negativeLevelHeight = -75042;
    auto negativeLevelHeightBelow = -75043;
    auto negativeLevelHeightAbove = -75040;
    auto minimumLevel = std::numeric_limits<int>::min();
    auto maximumLevel = std::numeric_limits<int>::max();

    levels.getOrCreateLevel(DummyType{ levelHeight });

    verifyIfHasLevels(levelHeight);

    verifyDoesNotHaveLevels(minimumLevel, negativeLevelHeightBelow,
            negativeLevelHeight, negativeLevelHeightAbove, -345, -3, -2, -1, 0,
            1, 2, 3, 345, levelHeightBelow, levelHeightAbove, maximumLevel);
}

TEST_F(MaxTreeLevelsTest, firstLevelHeightIsTheSameAsTheCreatedLevelHeight) {
    auto levelHeight = DummyType{ 14936 };

    levels.getOrCreateLevel(levelHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(levelHeight);
}

TEST_F(MaxTreeLevelsTest, firstLevelIsTheSameAsTheCreatedLevel) {
    auto levelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(levelHeight);
    auto& firstLevel = levels.getFirstLevel();

    assertThat(firstLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsTest, secondCreatedLevelHasCorrectHeight) {
    levels.getOrCreateLevel(DummyType{ 14931 });

    auto secondLevelHeight = DummyType{ 24931 };
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(secondLevel.getLevel()).isEqualTo(secondLevelHeight);
}

TEST_F(MaxTreeLevelsTest, secondCreatedLevelIsEmpty) {
    levels.getOrCreateLevel(DummyType{ 14931 });

    auto secondLevelHeight = DummyType{ 24931 };
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(secondLevel.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsTest, cantRecreateFirstLevelAfterCreatingSecondLevel) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(firstLevelHeight);

    levels.getOrCreateLevel(DummyType{ 61392 });

    auto& retrievedLevel = levels.getOrCreateLevel(firstLevelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsTest, firstAndSecondCreatedLevelsCanBeRetrieved) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto secondLevelHeight = DummyType{ 732 };
    auto& firstCreatedLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& secondRetrievedLevel = levels.getLevel(secondLevelHeight);
    auto& firstRetrievedLevel = levels.getLevel(firstLevelHeight);

    assertThat(firstRetrievedLevel).isAtSameAddressAs(firstCreatedLevel);
    assertThat(secondRetrievedLevel).isAtSameAddressAs(secondCreatedLevel);
}

TEST_F(MaxTreeLevelsTest,
        firstAndSecondCreatedLevelsCanBeRetrievedThroughConstReference) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto secondLevelHeight = DummyType{ 732 };
    auto& firstCreatedLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& secondRetrievedLevel = constLevels.getLevel(secondLevelHeight);
    auto& firstRetrievedLevel = constLevels.getLevel(firstLevelHeight);

    assertThat(firstRetrievedLevel).isAtSameAddressAs(firstCreatedLevel);
    assertThat(secondRetrievedLevel).isAtSameAddressAs(secondCreatedLevel);
}
