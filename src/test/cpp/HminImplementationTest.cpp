#include "HminImplementationTest.hpp"

TEST_F(HminImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(HminImplementationTest, isFilterImplementation) {
    using ImplementationClass = HminImplementation<SourceImageType,
            DestinationImageType>;
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_F(HminImplementationTest, isConstructibleWithParameters) {
    using FeatureSizeParameter = const SourcePixelType&;
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(With<FeatureSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}
