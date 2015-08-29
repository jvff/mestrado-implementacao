#include "WatershedImplementationTest.hpp"
#include "WatershedTests.hpp"

TEST_F(WatershedImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(WatershedImplementationTest, defaultSourceImageTypeIsGenericImage) {
    using ImplicitType = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = WatershedImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST_F(WatershedImplementationTest, isConstructible) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(
            With<SourceImageParameter, DestinationImageParameter>());
}

INSTANTIATE_TYPED_TEST_CASE_P(WatershedImplementationTest, WatershedTests,
        TestData<unsigned char>);
