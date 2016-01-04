#include "MaxTreeLevelsRemoveLevelsTest.hpp"

TEST_F(MaxTreeLevelsRemoveLevelsTest, removedLevelIsNotPresent) {
    auto height = DummyType{ 3 };

    levels.removeLevel(height);

    assertThat(levels.hasLevel(height)).isEqualTo(false);
}
