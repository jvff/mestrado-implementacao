#include "MinMaxTreeFilterAliasesTest.hpp"

TEST_F(MinMaxTreeFilterAliasesTest, aliasForMaxTreeFilterExists) {
    using MaxTreeFilterAlias = MaxTreeFilter<SourceImageType,
            InternalImageType>;
    using ExpectedType = MinMaxTreeFilter<SourceImageType, InternalImageType,
            std::less>;

    AssertThat<MaxTreeFilterAlias>::isTheSame(As<ExpectedType>());
}
