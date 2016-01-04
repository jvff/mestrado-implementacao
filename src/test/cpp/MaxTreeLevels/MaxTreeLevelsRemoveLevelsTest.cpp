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

TEST_F(MaxTreeLevelsRemoveLevelsTest, levelBeforeIsFoundCorrectlyAfterRemoval) {
    auto& secondLevel = levels.getLevel(DummyType{ 2 });

    levels.removeLevel(DummyType{ 3 });
    levels.removeLevel(DummyType{ 4 });

    auto& levelBeforeLast = levels.findLevelBefore(DummyType{ 5 });

    assertThat(levelBeforeLast).isAtSameAddressAs(secondLevel);
}
