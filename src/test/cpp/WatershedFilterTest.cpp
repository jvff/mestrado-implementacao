#include "WatershedFilterTest.hpp"
#include "WatershedTests.hpp"

TEST_F(WatershedFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(WatershedFilterTest, isSubClassOfComplexFilter) {
    using SubClass = DummyFilter;
    using SuperClass = ComplexFilter<SourceImageType, DestinationImageType,
            WatershedImplementation<SourceImageType, DestinationImageType> >;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST_F(WatershedFilterTest, isConstructible) {
    AssertThat<DummyFilter>::isConstructible(WithoutParameters());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(WatershedFilterTest, WatershedTests,
        TestData);
