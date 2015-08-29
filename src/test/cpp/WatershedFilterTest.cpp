#include "WatershedFilterTest.hpp"
#include "WatershedTests.hpp"

TEST_F(WatershedFilterTest, classTemplateExists) {
    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST_F(WatershedFilterTest, defaultSourceImageTypeIsGenericImage) {
    using ImplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType>;
    using ExplicitType = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}

TEST_F(WatershedFilterTest, isSubClassOfFilter) {
    using SubClass = WatershedFilter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST_F(WatershedFilterTest, isConstructible) {
    AssertThat<DummyFilter>::isConstructible(WithoutParameters());
}

INSTANTIATE_TYPED_TEST_CASE_P(WatershedFilterTest, WatershedTests,
        TestData<unsigned char>);
