#include "AreaOpeningAndClosingMinMaxTreeImplementationAliasesTest.hpp"

TEST_C(aliasForAreaOpeningMaxTreeImplementationExists) {
    using AreaOpeningMaxTreeImplementationAlias =
            AreaOpeningMaxTreeImplementation<SourceImageType,
                    DestinationImageType>;
    using ExpectedType = AreaOpeningAndClosingMinMaxTreeImplementation<
            SourceImageType, DestinationImageType, std::less>;

    AssertThat<AreaOpeningMaxTreeImplementationAlias>
            ::isTheSame(As<ExpectedType>());
}

TEST_C(aliasForAreaClosingMinTreeImplementationExists) {
    using AreaClosingMinTreeImplementationAlias =
            AreaClosingMinTreeImplementation<SourceImageType,
                    DestinationImageType>;
    using ExpectedType = AreaOpeningAndClosingMinMaxTreeImplementation<
            SourceImageType, DestinationImageType, std::greater>;

    AssertThat<AreaClosingMinTreeImplementationAlias>
            ::isTheSame(As<ExpectedType>());
}
