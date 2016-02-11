#include "MaxTreeLevelsTest.hpp"

using levelComparatorTypes = ::testing::Types<std::less<DummyType> >;

TYPED_TEST_CASE(MaxTreeLevelsTest, levelComparatorTypes);

TEST_C(MaxTreeLevelsTest, classTemplateExists) {
    AssertThat<DummyMaxTreeLevels>::isClassOrStruct();
}

TEST_C(MaxTreeLevelsTest, levelsCanBeRetrievedAsConstOrNot) {
    auto levelHeight = DummyType{ 12 };

    AssertThat<decltype(constLevels.getLevel(levelHeight))>::isConstReference();
    AssertThat<decltype(levels.getLevel(levelHeight))>::isNonConstReference();
}
