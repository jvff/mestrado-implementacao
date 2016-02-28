#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTree.hpp"
#include "MinTree.hpp"

#include "../DummyTypes.hpp"

TEST(MinMaxTreeAliasesTest, aliasForMaxTreeExists) {
    using MaxTreeAlias = MaxTree<DummyType>;
    using ExpectedType = MinMaxTree<DummyType, std::less<DummyType> >;

    AssertThat<MaxTreeAlias>::isTheSame(As<ExpectedType>());
}

TEST(MinMaxTreeAliasesTest, aliasForMinTreeExists) {
    using MinTreeAlias = MinTree<DummyType>;
    using ExpectedType = MinMaxTree<DummyType, std::greater<DummyType> >;

    AssertThat<MinTreeAlias>::isTheSame(As<ExpectedType>());
}
