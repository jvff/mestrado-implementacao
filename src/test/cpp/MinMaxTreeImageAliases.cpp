#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinTreeImage.hpp"
#include "MaxTreeImage.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

TEST(MinMaxTreeImageAliases, aliasForMaxTreeImageExists) {
    using InternalImageType = SimpleArrayImage<DummyType>;
    using MaxTreeImageAlias = MaxTreeImage<InternalImageType>;
    using ExpectedType = MinMaxTreeImage<InternalImageType,
            std::less<DummyType> >;

    AssertThat<MaxTreeImageAlias>::isTheSame(As<ExpectedType>());
}

TEST(MinMaxTreeImageAliases, aliasForMinTreeImageExists) {
    using InternalImageType = SimpleArrayImage<DummyType>;
    using MinTreeImageAlias = MinTreeImage<InternalImageType>;
    using ExpectedType = MinMaxTreeImage<InternalImageType,
            std::greater<DummyType> >;

    AssertThat<MinTreeImageAlias>::isTheSame(As<ExpectedType>());
}
