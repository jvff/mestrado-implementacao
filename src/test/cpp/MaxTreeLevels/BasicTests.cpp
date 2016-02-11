#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(BasicTests);

TEST_C(BasicTests, classTemplateExists) {
    AssertThat<DummyMinMaxTreeLevels>::isClassOrStruct();
}

TEST_C(BasicTests, levelsCanBeRetrievedAsConstOrNot) {
    auto levelHeight = DummyType{ 12 };

    AssertThat<decltype(constLevels.getLevel(levelHeight))>::isConstReference();
    AssertThat<decltype(levels.getLevel(levelHeight))>::isNonConstReference();
}
