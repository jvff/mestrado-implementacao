#include "HminFilterTest.hpp"

TEST_F(HminFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(HminFilterTest, isComplexFilter) {
    using ImplementationType = HminImplementation<SourceImageType,
            DestinationImageType>;
    using FilterClass = HminFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilter>());
}

TEST_F(HminFilterTest, isConstructibleWithParameter) {
    using FeatureHeightParameter = const SourcePixelType&;

    AssertThat<DummyFilter>::isConstructible(With<FeatureHeightParameter>());
}
