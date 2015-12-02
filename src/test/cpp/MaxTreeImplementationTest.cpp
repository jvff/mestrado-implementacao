#include "MaxTreeImplementationTest.hpp"
#include "MaxTreeTests.hpp"

TEST_F(MaxTreeImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST_F(MaxTreeImplementationTest, isFilterImplementation) {
    using ParentClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyImplementationType>::isSubClass(Of<ParentClass>());
}

TEST_F(MaxTreeImplementationTest, isConstructibleWithParameters) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementationType>::isConstructible(With<
            SourceImageParameter, DestinationImageParameter>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MaxTreeImplementationTest,
        MaxTreeTests, TestData);
