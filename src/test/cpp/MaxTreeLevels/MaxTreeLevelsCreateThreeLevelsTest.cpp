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
