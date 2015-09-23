#include "InversionImplementationTest.hpp"

TEST_F(InversionImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(InversionImplementationTest, isFilterImplementation) {
    using ImplementationType = DummyImplementation;
    using FilterImplementationType = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationType>::isSubClass(Of<FilterImplementationType>());
}

TEST_F(InversionImplementationTest, canBeConstructedWithoutExtraParameters) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(With<SourceImageParameter,
            DestinationImageParameter>());
}
