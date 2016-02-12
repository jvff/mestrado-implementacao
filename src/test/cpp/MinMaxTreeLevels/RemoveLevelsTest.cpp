#include "RemoveLevelsTest.hpp"

TEST_C(RemoveLevelsTest, removedLevelIsNotPresent) {
    auto height = DummyType{ 3 };

    levels.removeLevel(height);

    assertThat(levels.hasLevel(height)).isEqualTo(false);
}

TEST_C(RemoveLevelsTest, secondLevelBecomesFirstWhenFirstIsRemoved) {
    auto firstLevelHeight = levelHeights[0];
    auto secondLevelHeight = levelHeights[1];
    auto& secondLevel = levels.getLevel(secondLevelHeight);

    levels.removeLevel(firstLevelHeight);

    assertThat(levels.getFirstLevelHeight()).isEqualTo(secondLevelHeight);
    assertThat(levels.getFirstLevel()).isAtSameAddressAs(secondLevel);
}

TEST_C(RemoveLevelsTest, levelBeforeIsFoundCorrectlyAfterRemoval) {
    auto secondLevelHeight = levelHeights[1];
    auto thirdLevelHeight = levelHeights[2];
    auto fourthLevelHeight = levelHeights[3];
    auto fifthLevelHeight = levelHeights[4];

    auto& secondLevel = levels.getLevel(secondLevelHeight);

    levels.removeLevel(thirdLevelHeight);
    levels.removeLevel(fourthLevelHeight);

    auto& levelBeforeLast = levels.findLevelBefore(fifthLevelHeight);

    assertThat(levelBeforeLast).isAtSameAddressAs(secondLevel);
}
