#include "MinMaxTreeFilterTest.hpp"

using TreeTypeComparators = ::testing::Types<
        MinMaxTreeFilterTestAliases<std::less>,
        MinMaxTreeFilterTestAliases<std::greater> >;

TYPED_TEST_CASE(MinMaxTreeFilterTest, TreeTypeComparators);

TEST_C(classTemplateExists) {
    AssertThat<DummyMinMaxTreeFilter>::isClassOrStruct();
}

TEST_C(isComplexFilter) {
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<DummyMinMaxTreeFilter>::isSubClass(Of<ParentFilter>());
}

TEST_C(isConstructible) {
    AssertThat<DummyMinMaxTreeFilter>::isConstructible(WithoutParameters());
}
