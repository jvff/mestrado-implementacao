#include "InversionImplementationTest.hpp"
#include "InversionTests.hpp"

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

TEST_F(InversionImplementationTest, canBeConstructedWithOptionalParameters) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;
    using MinimumValueParameter = const SourcePixelType&;
    using MaximumValueParameter = const SourcePixelType&;

    AssertThat<DummyImplementation>::isConstructible(With<SourceImageParameter,
            DestinationImageParameter, MinimumValueParameter,
            MaximumValueParameter>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(InversionImplementationTest,
        InversionTests, TestData);
