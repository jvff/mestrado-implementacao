#include "MaxTreeLevelsTest.hpp"

TEST_F(MaxTreeLevelsTest, classTemplateExists) {
    AssertThat<DummyMaxTreeLevels>::isClassOrStruct();
}

TEST_F(MaxTreeLevelsTest, isInitiallyEmpty) {
    const DummyMaxTreeLevels levels;

    assertThat(levels.isEmpty()).isEqualTo(true);
}