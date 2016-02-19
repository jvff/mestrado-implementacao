#include "MaxTreeFilterTest.hpp"
#include "MinMaxTreeTests.hpp"

using TreeTypeComparators = ::testing::Types<ComparatorWrapper<std::less> >;

TYPED_TEST_CASE(MaxTreeFilterTest, TreeTypeComparators);

TEST_C(classTemplateExists) {
    AssertThat<DummyMaxTreeFilter>::isClassOrStruct();
}

TEST_C(isComplexFilter) {
    using DestinationImageType = MaxTreeImage<InternalImageType>;
    using ImplementationType = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<DummyMaxTreeFilter>::isSubClass(Of<ParentFilter>());
}

TEST_C(isConstructible) {
    AssertThat<DummyMaxTreeFilter>::isConstructible(WithoutParameters());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(MaxTreeFilterTest, MinMaxTreeTests,
        TestData);
