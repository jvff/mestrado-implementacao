#include "AreaOpeningMaxTreeImplementationTest.hpp"
#include "AreaOpeningTests.hpp"

TEST_F(AreaOpeningMaxTreeImplementationTest, classTemplateExists) {
    AssertThat<ImplementationClass>::isClassOrStruct();
}

TEST_F(AreaOpeningMaxTreeImplementationTest, isFilterImplementation) {
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_F(AreaOpeningMaxTreeImplementationTest, isConstructibleWithParameters) {
    using AreaSizeParameter = unsigned int;
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<ImplementationClass>::isConstructible(With<AreaSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(AreaOpeningMaxTreeImplementationTest,
        AreaOpeningTests, TestData);
