#include "BasicTests.hpp"

using TypeParameters = ::testing::Types<
    AreaOpeningAndClosingMinMaxTreeImplementationTestAliases<std::less> >;

TYPED_TEST_CASE(AreaOpeningAndClosingMinMaxTreeImplementationTest,
        TypeParameters);

TEST_C(classTemplateExists) {
    AssertThat<ImplementationClass>::isClassOrStruct();
}

TEST_C(isFilterImplementation) {
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_C(isConstructibleWithParameters) {
    using AreaSizeParameter = unsigned int;
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<ImplementationClass>::isConstructible(With<AreaSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}
