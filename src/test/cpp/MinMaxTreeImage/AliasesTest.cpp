#include "MinTreeImage.hpp"
#include "MaxTreeImage.hpp"

#include "MinMaxTreeImageTest.hpp"

SUB_TEST(AliasesTest);

TEST_C(AliasesTest, aliasForMaxTreeImageExists) {
    using InternalImageType = SimpleArrayImage<DummyType>;
    using MaxTreeImageAlias = MaxTreeImage<InternalImageType>;
    using ExpectedType = MinMaxTreeImage<InternalImageType,
            std::less<DummyType> >;

    AssertThat<MaxTreeImageAlias>::isTheSame(As<ExpectedType>());
}

TEST_C(AliasesTest, aliasForMinTreeImageExists) {
    using InternalImageType = SimpleArrayImage<DummyType>;
    using MinTreeImageAlias = MinTreeImage<InternalImageType>;
    using ExpectedType = MinMaxTreeImage<InternalImageType,
            std::greater<DummyType> >;

    AssertThat<MinTreeImageAlias>::isTheSame(As<ExpectedType>());
}
