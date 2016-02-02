#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

TEST(MinMaxTreeNodeAliasTest, aliasForMaxTreeNodeExists) {
    using MaxTreeNodeAlias = MaxTreeNode<DummyType>;
    using ExpectedType = MinMaxTreeNode<DummyType, std::less<DummyType> >;

    AssertThat<MaxTreeNodeAlias>::isTheSame(As<ExpectedType>());
}
