#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevels.hpp"

#include "../DummyTypes.hpp"

TEST(MaxTreeLevelsAliasesTest, MaxTreeLevelsAliasExists) {
    using MaxTreeLevelsAlias = MaxTreeLevels<DummyType>;
    using ExpectedType = MinMaxTreeLevels<DummyType, std::less<DummyType> >;

    AssertThat<MaxTreeLevelsAlias>::isTheSame(As<ExpectedType>());
}
