#include "MaxTreeLevelsCreateThreeLevelsTest.hpp"

TEST_F(MaxTreeLevelsCreateThreeLevelsTest, thirdCreatedLevelHasCorrectHeight) {
    levels.getOrCreateLevel(DummyType{ 14931 });
    levels.getOrCreateLevel(DummyType{ 23098 });

    auto thirdLevelHeight = DummyType{ 78427 };
    auto& thirdLevel = levels.getOrCreateLevel(thirdLevelHeight);

    assertThat(thirdLevel.getLevel()).isEqualTo(thirdLevelHeight);
}
