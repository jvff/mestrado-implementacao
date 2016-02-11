#include "MinMaxTreeLevelsTest.hpp"

using levelComparatorTypes = ::testing::Types<std::less<DummyType>,
        std::greater<DummyType> >;

TYPED_TEST_CASE(MinMaxTreeLevelsTest, levelComparatorTypes);

TEST_C(MinMaxTreeLevelsTest, classTemplateExists) {
    AssertThat<DummyMinMaxTreeLevels>::isClassOrStruct();
}

TEST_C(MinMaxTreeLevelsTest, levelsCanBeRetrievedAsConstOrNot) {
    auto levelHeight = DummyType{ 12 };

    AssertThat<decltype(constLevels.getLevel(levelHeight))>::isConstReference();
    AssertThat<decltype(levels.getLevel(levelHeight))>::isNonConstReference();
}
