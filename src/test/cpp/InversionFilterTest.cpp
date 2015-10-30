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

TEST_F(InversionFilterTest, hasDefaultConstructor) {
    AssertThat<DummyFilterType>::isConstructible(WithoutParameters());
}

TEST_F(InversionFilterTest, hasConstructorForManualValues) {
    using MinimumValueParameter = const SourcePixelType&;
    using MaximumValueParameter = const SourcePixelType&;

    AssertThat<DummyFilterType>::isConstructible(
            With<MinimumValueParameter, MaximumValueParameter>());
}
