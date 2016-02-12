#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(CreateThreeLevelsTest);

TEST_C(CreateThreeLevelsTest, thirdCreatedLevelHasCorrectHeight) {
    levels.getOrCreateLevel(DummyType{ 14931 });
    levels.getOrCreateLevel(DummyType{ 23098 });

    auto thirdLevelHeight = DummyType{ 78427 };
    auto& thirdLevel = levels.getOrCreateLevel(thirdLevelHeight);

    assertThat(thirdLevel.getLevel()).isEqualTo(thirdLevelHeight);
}

TEST_C(CreateThreeLevelsTest, thirdCreatedLevelIsEmpty) {
    levels.getOrCreateLevel(DummyType{ 14931 });
    levels.getOrCreateLevel(DummyType{ 20398 });

    auto thirdLevelHeight = DummyType{ 24971 };
    auto& thirdLevel = levels.getOrCreateLevel(thirdLevelHeight);

    assertThat(thirdLevel.isEmpty()).isEqualTo(true);
}

TEST_C(CreateThreeLevelsTest, cantRecreateFirstLevelAfterCreatingThirdLevel) {
    auto firstLevelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(firstLevelHeight);

    levels.getOrCreateLevel(DummyType{ 61392 });
    levels.getOrCreateLevel(DummyType{ 89723 });

    auto& retrievedLevel = levels.getOrCreateLevel(firstLevelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_C(CreateThreeLevelsTest, cantRecreateSecondLevelAfterCreatingThirdLevel) {
    levels.getOrCreateLevel(DummyType{ 109 });

    auto secondLevelHeight = DummyType{ 59783 };
    auto& createdLevel = levels.getOrCreateLevel(secondLevelHeight);

    levels.getOrCreateLevel(DummyType{ 89723 });

    auto& retrievedLevel = levels.getOrCreateLevel(secondLevelHeight);

    assertThat(retrievedLevel).isAtSameAddressAs(createdLevel);
}

TEST_C(CreateThreeLevelsTest, firstSecondAndThirdCreatedLevelsCanBeRetrieved) {
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

TEST_C(CreateThreeLevelsTest,
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

TEST_C(CreateThreeLevelsTest, isNotEmptyAfterCreatingThreeLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });
    levels.getOrCreateLevel(DummyType{ 45980 });

    assertThat(constLevels.isEmpty()).isEqualTo(false);
}

TEST_C(CreateThreeLevelsTest, hasThreeLevelsAfterCreatingThreeLevels) {
    levels.getOrCreateLevel(DummyType{ 74931 });
    levels.getOrCreateLevel(DummyType{ 34028 });
    levels.getOrCreateLevel(DummyType{ 45980 });

    assertThat(constLevels.numberOfLevels()).isEqualTo(3u);
}

TEST_C(CreateThreeLevelsTest, hasCreatedLevels) {
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

TEST_C(CreateThreeLevelsTest,
        firstLevelHeightIsTheSameAsTheThirdCreatedLevelHeight) {
    auto firstHeight = DummyType{ 247001 };
    auto secondHeight = DummyType{ 100000 };
    auto thirdHeight = DummyType{ 93482 };
    auto firstLevelHeight = getFirstLevelHeightFrom(firstHeight, secondHeight,
            thirdHeight);

    levels.getOrCreateLevel(firstHeight);
    levels.getOrCreateLevel(secondHeight);
    levels.getOrCreateLevel(thirdHeight);

    assertThat(constLevels.getFirstLevelHeight()).isEqualTo(firstLevelHeight);
}

TEST_C(CreateThreeLevelsTest, firstLevelIsTheSameAsTheThirdCreatedLevel) {
    auto& firstCreatedLevel = levels.getOrCreateLevel(DummyType{ 61200 });
    auto& secondCreatedLevel = levels.getOrCreateLevel(DummyType{ 59783 });
    auto& thirdCreatedLevel = levels.getOrCreateLevel(DummyType{ 42794 });
    auto& expectedFirstLevel = getFirstLevelFrom(firstCreatedLevel,
            secondCreatedLevel, thirdCreatedLevel);
    auto& firstLevel = levels.getFirstLevel();

    assertThat(firstLevel).isAtSameAddressAs(expectedFirstLevel);
}

TEST_C(CreateThreeLevelsTest, findsLevelBeforeLast) {
    auto firstHeight = DummyType{ 45 };
    auto secondHeight = DummyType{ 23 };
    auto thirdHeight = DummyType{ 71 };

    auto& firstCreatedLevel = levels.getOrCreateLevel(firstHeight);
    auto& secondCreatedLevel = levels.getOrCreateLevel(secondHeight);
    auto& thirdCreatedLevel = levels.getOrCreateLevel(thirdHeight);

    auto& secondLevel = getSecondLevelFrom(firstCreatedLevel,
            secondCreatedLevel, thirdCreatedLevel);
    auto lastLevelHeight = getLastLevelHeightFrom(firstHeight, secondHeight,
            thirdHeight);

    auto& levelBeforeThird = levels.findLevelBefore(lastLevelHeight);

    assertThat(levelBeforeThird).isAtSameAddressAs(secondLevel);
}
