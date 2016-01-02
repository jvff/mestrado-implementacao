#include "MaxTreeLevelsCreateTwoLevelsTest.hpp"

TEST_F(MaxTreeLevelsCreateTwoLevelsTest, secondCreatedLevelHasCorrectHeight) {
    levels.getOrCreateLevel(DummyType{ 14931 });

    auto secondLevelHeight = DummyType{ 24931 };
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(secondLevel.getLevel()).isEqualTo(secondLevelHeight);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest, secondCreatedLevelIsEmpty) {
    levels.getOrCreateLevel(DummyType{ 14931 });

    auto secondLevelHeight = DummyType{ 24931 };
    auto& secondLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(secondLevel.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest,
        cantRecreateFirstLevelAfterCreatingSecondLevel) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(firstLevelHeight);

    levels.getOrCreateLevel(DummyType{ 61392 });

    auto& retrievedLevel = levels.getOrCreateLevel(firstLevelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest,
        firstAndSecondCreatedLevelsCanBeRetrieved) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto secondLevelHeight = DummyType{ 732 };
    auto& firstCreatedLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondLevelHeight);

    auto& secondRetrievedLevel = levels.getLevel(secondLevelHeight);
    auto& firstRetrievedLevel = levels.getLevel(firstLevelHeight);

    assertThat(firstRetrievedLevel).isAtSameAddressAs(firstCreatedLevel);
    assertThat(secondRetrievedLevel).isAtSameAddressAs(secondCreatedLevel);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest,
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

TEST_F(MaxTreeLevelsCreateTwoLevelsTest, isNotEmptyAfterCreatingTwoLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });

    assertThat(constLevels.isEmpty()).isEqualTo(false);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest, hasTwoLevelsAfterCreatingTwoLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });

    assertThat(constLevels.numberOfLevels()).isEqualTo(2u);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest, hasCreatedLevels) {
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

TEST_F(MaxTreeLevelsCreateTwoLevelsTest,
        firstLevelHeightIsTheSameAsTheFirstCreatedLevelHeight) {
    auto firstLevelHeight = DummyType{ 93482 };
    auto secondLevelHeight = DummyType{ 247001 };

    levels.getOrCreateLevel(firstLevelHeight);
    levels.getOrCreateLevel(secondLevelHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(firstLevelHeight);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest,
        firstLevelHeightIsTheSameAsTheSecondCreatedLevelHeight) {
    auto firstLevelHeight = DummyType{ 93482 };
    auto secondLevelHeight = DummyType{ 247001 };

    levels.getOrCreateLevel(secondLevelHeight);
    levels.getOrCreateLevel(firstLevelHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(firstLevelHeight);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest,
        firstLevelIsTheSameAsTheFirstCreatedLevel) {
    auto& firstCreatedLevel = levels.getOrCreateLevel(DummyType{ 59783 });

    levels.getOrCreateLevel(DummyType{ 61200 });

    auto& firstLevel = levels.getFirstLevel();

    assertThat(firstLevel).isAtSameAddressAs(firstCreatedLevel);
}

TEST_F(MaxTreeLevelsCreateTwoLevelsTest,
        firstLevelIsTheSameAsTheSecondCreatedLevel) {
    levels.getOrCreateLevel(DummyType{ 61200 });

    auto& secondCreatedLevel = levels.getOrCreateLevel(DummyType{ 59783 });
    auto& firstLevel = levels.getFirstLevel();

    assertThat(firstLevel).isAtSameAddressAs(secondCreatedLevel);
}
