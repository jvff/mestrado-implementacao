#include "MaxTreeLevelsRemoveLevelsTest.hpp"

TEST_F(MaxTreeLevelsRemoveLevelsTest, removedLevelIsNotPresent) {
    auto height = DummyType{ 3 };

    levels.removeLevel(height);

    assertThat(levels.hasLevel(height)).isEqualTo(false);
}

TEST_F(MaxTreeLevelsRemoveLevelsTest,
        secondLevelBecomesFirstWhenFirstIsRemoved) {
    auto secondLevelHeight = DummyType{ 2 };
    auto& secondLevel = levels.getLevel(secondLevelHeight);

    levels.removeLevel(DummyType{ 1 });

    assertThat(levels.getFirstLevelHeight()).isEqualTo(secondLevelHeight);
    assertThat(levels.getFirstLevel()).isAtSameAddressAs(secondLevel);
}
