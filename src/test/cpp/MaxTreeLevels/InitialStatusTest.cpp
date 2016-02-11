#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(InitialStatusTest);

TEST_C(InitialStatusTest, isInitiallyEmpty) {
    assertThat(constLevels.isEmpty()).isEqualTo(true);
}

TEST_C(InitialStatusTest, initiallyHasZeroLevels) {
    assertThat(constLevels.numberOfLevels()).isEqualTo(0u);
}

TEST_C(InitialStatusTest, initiallHasNoLevels) {
    verifyDoesNotHaveLevels(minimumLevel, -345, -3, -2, -1, 0, 1, 2, 3, 345,
            75042, maximumLevel);
}
