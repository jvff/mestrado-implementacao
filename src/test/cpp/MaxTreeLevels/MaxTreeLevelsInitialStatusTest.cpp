#include "MaxTreeLevelsInitialStatusTest.hpp"

TEST_F(MaxTreeLevelsInitialStatusTest, isInitiallyEmpty) {
    assertThat(constLevels.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsInitialStatusTest, initiallyHasZeroLevels) {
    assertThat(constLevels.numberOfLevels()).isEqualTo(0u);
}

TEST_F(MaxTreeLevelsInitialStatusTest, initiallHasNoLevels) {
    verifyDoesNotHaveLevels(minimumLevel, -345, -3, -2, -1, 0, 1, 2, 3, 345,
            75042, maximumLevel);
}
