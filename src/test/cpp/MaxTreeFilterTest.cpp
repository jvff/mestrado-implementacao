#include "MaxTreeFilterTest.hpp"

TEST_F(MaxTreeFilterTest, classTemplateExists) {
    AssertThat<DummyMaxTreeFilter>::isClassOrStruct();
}

TEST_F(MaxTreeFilterTest, isComplexFilter) {
    using DestinationImageType = MaxTreeImage<InternalImageType>;
    using ImplementationType = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<DummyMaxTreeFilter>::isSubClass(Of<ParentFilter>());
}

TEST_F(MaxTreeFilterTest, isConstructible) {
    AssertThat<DummyMaxTreeFilter>::isConstructible(WithoutParameters());
}
