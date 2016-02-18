#include "MinMaxTreeImplementationAliasesTest.hpp"

TEST_F(MinMaxTreeImplementationAliasesTest,
        aliasForMaxTreeImplementationExists) {
    using MaxTreeImplementationAlias = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
    using ExpectedType = MinMaxTreeImplementation<SourceImageType,
            InternalImageType, std::less>;

    AssertThat<MaxTreeImplementationAlias>::isTheSame(As<ExpectedType>());
}
