#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"
#include "MinTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MinMaxTreeNodeAliasesTest, aliasForMaxTreeNodeExists) {
    using MaxTreeNodeAlias = MaxTreeNode<DummyType>;
    using ExpectedType = MinMaxTreeNode<DummyType, std::less<DummyType> >;

    AssertThat<MaxTreeNodeAlias>::isTheSame(As<ExpectedType>());
}

TEST(MinMaxTreeNodeAliasesTest, aliasForMinTreeNodeExists) {
    using MinTreeNodeAlias = MinTreeNode<DummyType>;
    using ExpectedType = MinMaxTreeNode<DummyType, std::greater<DummyType> >;

    AssertThat<MinTreeNodeAlias>::isTheSame(As<ExpectedType>());
}
