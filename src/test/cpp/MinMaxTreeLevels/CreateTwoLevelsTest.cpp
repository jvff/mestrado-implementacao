#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(CreateTwoLevelsTest);

TEST_C(CreateTwoLevelsTest, secondCreatedLevelHasCorrectHeight) {
    levels.getOrCreateLevel(DummyType{ 14931 });

    auto secondLevelHeight = DummyType{ 24931 };
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(secondLevel.getLevel()).isEqualTo(secondLevelHeight);
}

TEST_C(CreateTwoLevelsTest, secondCreatedLevelIsEmpty) {
    levels.getOrCreateLevel(DummyType{ 14931 });

    auto secondLevelHeight = DummyType{ 24931 };
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(secondLevel.isEmpty()).isEqualTo(true);
}

TEST_C(CreateTwoLevelsTest, cantRecreateFirstLevelAfterCreatingSecondLevel) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(firstLevelHeight);

    levels.getOrCreateLevel(DummyType{ 61392 });

    auto& retrievedLevel = levels.getOrCreateLevel(firstLevelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_C(CreateTwoLevelsTest, firstAndSecondCreatedLevelsCanBeRetrieved) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto secondLevelHeight = DummyType{ 732 };
    auto& firstCreatedLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& secondRetrievedLevel = levels.getLevel(secondLevelHeight);
    auto& firstRetrievedLevel = levels.getLevel(firstLevelHeight);

    assertThat(firstRetrievedLevel).isAtSameAddressAs(firstCreatedLevel);
    assertThat(secondRetrievedLevel).isAtSameAddressAs(secondCreatedLevel);
}

TEST_C(CreateTwoLevelsTest,
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

TEST_C(CreateTwoLevelsTest, isNotEmptyAfterCreatingTwoLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });

    assertThat(constLevels.isEmpty()).isEqualTo(false);
}

TEST_C(CreateTwoLevelsTest, hasTwoLevelsAfterCreatingTwoLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });

    assertThat(constLevels.numberOfLevels()).isEqualTo(2u);
}

TEST_C(CreateTwoLevelsTest, hasCreatedLevels) {
    auto firstLevelHeight = 75042;
    auto secondLevelHeight = 345789;

    levels.getOrCreateLevel(DummyType{ firstLevelHeight });
    levels.getOrCreateLevel(DummyType{ secondLevelHeight });

    verifyIfHasLevels(firstLevelHeight, secondLevelHeight);

    verifyDoesNotHaveLevels(minimumLevel,
            -firstLevelHeight, -firstLevelHeight - 1, -firstLevelHeight + 1,
            -secondLevelHeight, -secondLevelHeight - 1, -secondLevelHeight + 1,
            -345, -3, -2, -1, 0, 1, 2, 3, 345,
            firstLevelHeight - 1, firstLevelHeight + 1,
            secondLevelHeight - 1, secondLevelHeight + 1,
            maximumLevel);
}

TEST_C(CreateTwoLevelsTest,
        firstLevelHeightIsTheSameAsTheFirstCreatedLevelHeight) {
    auto firstHeight = DummyType{ 93482 };
    auto secondHeight = DummyType{ 247001 };
    auto firstLevelHeight = getFirstLevelHeightFrom(firstHeight, secondHeight);

    levels.getOrCreateLevel(firstHeight);
    levels.getOrCreateLevel(secondHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(firstLevelHeight);
}

TEST_C(CreateTwoLevelsTest,
        firstLevelHeightIsTheSameAsTheSecondCreatedLevelHeight) {
    auto firstHeight = DummyType{ 247001 };
    auto secondHeight = DummyType{ 93482 };
    auto firstLevelHeight = getFirstLevelHeightFrom(firstHeight, secondHeight);

    levels.getOrCreateLevel(firstHeight);
    levels.getOrCreateLevel(secondHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(firstLevelHeight);
}

TEST_C(CreateTwoLevelsTest, firstLevelIsTheSameAsTheFirstCreatedLevel) {
    auto& firstCreatedLevel = levels.getOrCreateLevel(DummyType{ 59783 });
    auto& secondCreatedLevel = levels.getOrCreateLevel(DummyType{ 61200 });
    auto& expectedFirstLevel = getFirstLevelFrom(firstCreatedLevel,
            secondCreatedLevel);
    auto& firstLevel = levels.getFirstLevel();

    assertThat(firstLevel).isAtSameAddressAs(expectedFirstLevel);
}

TEST_C(CreateTwoLevelsTest, firstLevelIsTheSameAsTheSecondCreatedLevel) {
    auto& firstCreatedLevel = levels.getOrCreateLevel(DummyType{ 61200 });
    auto& secondCreatedLevel = levels.getOrCreateLevel(DummyType{ 59783 });
    auto& expectedFirstLevel = getFirstLevelFrom(firstCreatedLevel,
            secondCreatedLevel);
    auto& firstLevel = levels.getFirstLevel();

    assertThat(firstLevel).isAtSameAddressAs(expectedFirstLevel);
}

TEST_C(CreateTwoLevelsTest, findsLevelBeforeLast) {
    auto firstHeight = DummyType{ 23 };
    auto secondHeight = DummyType{ 71 };

    auto& firstCreatedLevel = levels.getOrCreateLevel(firstHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondHeight);

    auto& firstLevel = getFirstLevelFrom(firstCreatedLevel, secondCreatedLevel);
    auto secondLevelHeight = getLastLevelHeightFrom(firstHeight, secondHeight);

    auto& levelBeforeSecond = levels.findLevelBefore(secondLevelHeight);

    assertThat(levelBeforeSecond).isAtSameAddressAs(firstLevel);
}
