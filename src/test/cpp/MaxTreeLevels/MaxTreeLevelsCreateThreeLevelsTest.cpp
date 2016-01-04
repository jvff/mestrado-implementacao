#include "MaxTreeLevelsCreateThreeLevelsTest.hpp"

TEST_F(MaxTreeLevelsCreateThreeLevelsTest, thirdCreatedLevelHasCorrectHeight) {
    levels.getOrCreateLevel(DummyType{ 14931 });
    levels.getOrCreateLevel(DummyType{ 23098 });

    auto thirdLevelHeight = DummyType{ 78427 };
    auto& thirdLevel = levels.getOrCreateLevel(thirdLevelHeight);

    assertThat(thirdLevel.getLevel()).isEqualTo(thirdLevelHeight);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest, thirdCreatedLevelIsEmpty) {
    levels.getOrCreateLevel(DummyType{ 14931 });
    levels.getOrCreateLevel(DummyType{ 20398 });

    auto thirdLevelHeight = DummyType{ 24971 };
    auto& thirdLevel = levels.getOrCreateLevel(thirdLevelHeight);

    assertThat(thirdLevel.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest,
        cantRecreateFirstLevelAfterCreatingThirdLevel) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(firstLevelHeight);

    levels.getOrCreateLevel(DummyType{ 61392 });
    levels.getOrCreateLevel(DummyType{ 89723 });

    auto& retrievedLevel = levels.getOrCreateLevel(firstLevelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest,
        cantRecreateSecondLevelAfterCreatingThirdLevel) {
    levels.getOrCreateLevel(DummyType{ 109 });

    auto secondLevelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(secondLevelHeight);

    levels.getOrCreateLevel(DummyType{ 89723 });

    auto& retrievedLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest,
        firstSecondAndThirdCreatedLevelsCanBeRetrieved) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto secondLevelHeight = DummyType{ 732 };
    auto thirdLevelHeight = DummyType{ 4378 };
    auto& firstCreatedLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondLevelHeight);
    auto& thirdCreatedLevel = levels.getOrCreateLevel(thirdLevelHeight);

    auto& thirdRetrievedLevel = levels.getLevel(thirdLevelHeight);
    auto& secondRetrievedLevel = levels.getLevel(secondLevelHeight);
    auto& firstRetrievedLevel = levels.getLevel(firstLevelHeight);

    assertThat(firstRetrievedLevel).isAtSameAddressAs(firstCreatedLevel);
    assertThat(secondRetrievedLevel).isAtSameAddressAs(secondCreatedLevel);
    assertThat(thirdRetrievedLevel).isAtSameAddressAs(thirdCreatedLevel);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest,
        firstSecondAndThirdCreatedLevelsCanBeRetrievedThroughConstReference) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto secondLevelHeight = DummyType{ 732 };
    auto thirdLevelHeight = DummyType{ 4378 };
    auto& firstCreatedLevel = levels.getOrCreateLevel(firstLevelHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondLevelHeight);
    auto& thirdCreatedLevel = levels.getOrCreateLevel(thirdLevelHeight);

    auto& thirdRetrievedLevel = constLevels.getLevel(thirdLevelHeight);
    auto& secondRetrievedLevel = constLevels.getLevel(secondLevelHeight);
    auto& firstRetrievedLevel = constLevels.getLevel(firstLevelHeight);

    assertThat(firstRetrievedLevel).isAtSameAddressAs(firstCreatedLevel);
    assertThat(secondRetrievedLevel).isAtSameAddressAs(secondCreatedLevel);
    assertThat(thirdRetrievedLevel).isAtSameAddressAs(thirdCreatedLevel);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest, isNotEmptyAfterCreatingThreeLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });
    levels.getOrCreateLevel(DummyType{ 45980 });

    assertThat(constLevels.isEmpty()).isEqualTo(false);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest,
        hasThreeLevelsAfterCreatingThreeLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });
    levels.getOrCreateLevel(DummyType{ 45980 });

    assertThat(constLevels.numberOfLevels()).isEqualTo(3u);
}

TEST_F(MaxTreeLevelsCreateThreeLevelsTest, hasCreatedLevels) {
    auto firstLevelHeight = 75042;
    auto secondLevelHeight = 345789;
    auto thirdLevelHeight = 87942;

    levels.getOrCreateLevel(DummyType{ firstLevelHeight });
    levels.getOrCreateLevel(DummyType{ secondLevelHeight });
    levels.getOrCreateLevel(DummyType{ thirdLevelHeight });

    verifyIfHasLevels(firstLevelHeight, secondLevelHeight, thirdLevelHeight);

    verifyDoesNotHaveLevels(minimumLevel,
            -firstLevelHeight, -firstLevelHeight - 1, -firstLevelHeight + 1,
            -secondLevelHeight, -secondLevelHeight - 1, -secondLevelHeight + 1,
            -thirdLevelHeight, -thirdLevelHeight - 1, -thirdLevelHeight + 1,
            -345, -3, -2, -1, 0, 1, 2, 3, 345,
            firstLevelHeight - 1, firstLevelHeight + 1,
            secondLevelHeight - 1, secondLevelHeight + 1,
            thirdLevelHeight - 1, thirdLevelHeight + 1,
            maximumLevel);
}
