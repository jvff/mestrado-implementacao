#include "MaxTreeLevelsTest.hpp"

TEST_F(MaxTreeLevelsTest, classTemplateExists) {
    AssertThat<DummyMaxTreeLevels>::isClassOrStruct();
}

TEST_F(MaxTreeLevelsTest, levelsCanBeRetrievedAsConstOrNot) {
    auto levelHeight = DummyType{ 12 };

    AssertThat<decltype(constLevels.getLevel(levelHeight))>::isConstReference();
    AssertThat<decltype(levels.getLevel(levelHeight))>::isNonConstReference();
}
