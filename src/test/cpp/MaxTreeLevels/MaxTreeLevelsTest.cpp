#include "MaxTreeLevelsTest.hpp"

using levelComparatorTypes = ::testing::Types<std::less<DummyType> >;

TYPED_TEST_CASE(MaxTreeLevelsTest, levelComparatorTypes);

TEST_C(classTemplateExists) {
    AssertThat<DummyMaxTreeLevels>::isClassOrStruct();
}

TEST_C(levelsCanBeRetrievedAsConstOrNot) {
    auto levelHeight = DummyType{ 12 };

    AssertThat<decltype(constLevels.getLevel(levelHeight))>::isConstReference();
    AssertThat<decltype(levels.getLevel(levelHeight))>::isNonConstReference();
}
