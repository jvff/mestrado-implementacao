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
