#include "MaxTreeImplementationTest.hpp"
#include "MaxTreeTests.hpp"

using TreeTypeComparators = ::testing::Types<ComparatorWrapper<std::less> >;

TYPED_TEST_CASE(MaxTreeImplementationTest, TreeTypeComparators);

TEST_C(classTemplateExists) {
    AssertThat<DummyImplementationType>::isClassOrStruct();
}

TEST_C(isFilterImplementation) {
    using ParentClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyImplementationType>::isSubClass(Of<ParentClass>());
}

TEST_C(isConstructibleWithParameters) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementationType>::isConstructible(With<
            SourceImageParameter, DestinationImageParameter>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MaxTreeImplementationTest,
        MaxTreeTests, TestData);
