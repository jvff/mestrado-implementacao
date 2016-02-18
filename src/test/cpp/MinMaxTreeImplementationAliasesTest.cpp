#include "MinMaxTreeImplementationAliasesTest.hpp"

TEST_F(MinMaxTreeImplementationAliasesTest,
        aliasForMaxTreeImplementationExists) {
    using MaxTreeImplementationAlias = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
    using ExpectedType = MinMaxTreeImplementation<SourceImageType,
            InternalImageType, std::less>;

    AssertThat<MaxTreeImplementationAlias>::isTheSame(As<ExpectedType>());
}

TEST_F(MinMaxTreeImplementationAliasesTest,
        aliasForMinTreeImplementationExists) {
    using MinTreeImplementationAlias = MinTreeImplementation<SourceImageType,
            InternalImageType>;
    using ExpectedType = MinMaxTreeImplementation<SourceImageType,
            InternalImageType, std::greater>;

    AssertThat<MinTreeImplementationAlias>::isTheSame(As<ExpectedType>());
}
