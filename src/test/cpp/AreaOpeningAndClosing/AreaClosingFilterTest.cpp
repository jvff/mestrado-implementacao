#include "AreaClosingFilterTest.hpp"
#include "AreaClosingTests.hpp"

TEST(AreaClosingFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AreaClosingFilter<Image<DummyType>, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(AreaClosingFilterTest, isComplexFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using FilterClass = AreaClosingFilter<SourceImageType,
            DestinationImageType>;
    using ImplementationClass = AreaClosingImplementation<SourceImageType,
            DestinationImageType>;
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationClass>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilter>());
}

TEST(AreaClosingFilterTest, isConstructibleWithParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = AreaClosingFilter<SourceImageType,
            DestinationImageType>;
    using AreaSizeParameter = unsigned int;

    AssertThat<DummyFilter>::isConstructible(With<AreaSizeParameter>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(AreaClosingFilterTest, AreaClosingTests,
        TestData);
