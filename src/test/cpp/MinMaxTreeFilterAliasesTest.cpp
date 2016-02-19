#include "MinMaxTreeFilterAliasesTest.hpp"

TEST_F(MinMaxTreeFilterAliasesTest, aliasForMaxTreeFilterExists) {
    using MaxTreeFilterAlias = MaxTreeFilter<SourceImageType,
            InternalImageType>;
    using ExpectedType = MinMaxTreeFilter<SourceImageType, InternalImageType,
            std::less>;

    AssertThat<MaxTreeFilterAlias>::isTheSame(As<ExpectedType>());
}

TEST_F(MinMaxTreeFilterAliasesTest, aliasForMinTreeFilterExists) {
    using MinTreeFilterAlias = MinTreeFilter<SourceImageType,
            InternalImageType>;
    using ExpectedType = MinMaxTreeFilter<SourceImageType, InternalImageType,
            std::greater>;

    AssertThat<MinTreeFilterAlias>::isTheSame(As<ExpectedType>());
}
