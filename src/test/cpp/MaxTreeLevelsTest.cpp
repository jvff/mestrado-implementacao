#include "MaxTreeLevelsTest.hpp"

TEST_F(MaxTreeLevelsTest, classTemplateExists) {
    AssertThat<DummyMaxTreeLevels>::isClassOrStruct();
}

TEST_F(MaxTreeLevelsTest, isInitiallyEmpty) {
    assertThat(constLevels.isEmpty()).isEqualTo(true);
}

TEST_F(MaxTreeLevelsTest, initiallyHasZeroLevels) {
    assertThat(constLevels.numberOfLevels()).isEqualTo(0u);
}
