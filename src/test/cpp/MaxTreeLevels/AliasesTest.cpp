#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevels.hpp"
#include "MinTreeLevels.hpp"

#include "../DummyTypes.hpp"

TEST(MinMaxTreeLevelsAliasesTest, MaxTreeLevelsAliasExists) {
    using MaxTreeLevelsAlias = MaxTreeLevels<DummyType>;
    using ExpectedType = MinMaxTreeLevels<DummyType, std::less<DummyType> >;

    AssertThat<MaxTreeLevelsAlias>::isTheSame(As<ExpectedType>());
}

TEST(MinMaxTreeLevelsAliasesTest, MinTreeLevelsAliasExists) {
    using MinTreeLevelsAlias = MinTreeLevels<DummyType>;
    using ExpectedType = MinMaxTreeLevels<DummyType, std::greater<DummyType> >;

    AssertThat<MinTreeLevelsAlias>::isTheSame(As<ExpectedType>());
}
