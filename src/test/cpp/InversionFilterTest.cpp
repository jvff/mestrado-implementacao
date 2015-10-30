#include "InversionFilterTest.hpp"

TEST_F(InversionFilterTest, classTemplateExists) {
    AssertThat<DummyFilterType>::isClassOrStruct();
}

TEST_F(InversionFilterTest, isComplexFilter) {
    using FilterClass = DummyFilterType;
    using ParentFilterClass = ComplexFilter<SourceImageType,
            DestinationImageType, ImplementationType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}
