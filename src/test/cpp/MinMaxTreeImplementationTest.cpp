#include "MinMaxTreeImplementationTest.hpp"

using TreeTypeComparators = ::testing::Types<ComparatorWrapper<std::less>,
        ComparatorWrapper<std::greater> >;

TYPED_TEST_CASE(MinMaxTreeImplementationTest, TreeTypeComparators);

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
