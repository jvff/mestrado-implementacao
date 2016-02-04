#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevel.hpp"
#include "MinTreeLevel.hpp"

#include "DummyTypes.hpp"

TEST(MinMaxTreeLevelAliasesTest, MaxTreeLevelAliasExists) {
    using MaxTreeLevelAlias = MaxTreeLevel<DummyType>;
    using ExpectedType = MinMaxTreeLevel<DummyType, std::less<DummyType> >;

    AssertThat<MaxTreeLevelAlias>::isTheSame(As<ExpectedType>());
}

TEST(MinMaxTreeLevelAliasesTest, MinTreeLevelAliasExists) {
    using MinTreeLevelAlias = MinTreeLevel<DummyType>;
    using ExpectedType = MinMaxTreeLevel<DummyType, std::greater<DummyType> >;

    AssertThat<MinTreeLevelAlias>::isTheSame(As<ExpectedType>());
}
