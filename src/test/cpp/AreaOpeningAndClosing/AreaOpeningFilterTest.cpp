#include "AreaOpeningFilterTest.hpp"
#include "AreaOpeningTests.hpp"

TEST(AreaOpeningFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = AreaOpeningFilter<Image<DummyType>, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(AreaOpeningFilterTest, isComplexFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationType = AreaOpeningImplementation<SourceImageType,
            DestinationImageType>;
    using SubClass = AreaOpeningFilter<SourceImageType, DestinationImageType>;
    using SuperClass = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

TEST(AreaOpeningFilterTest, isConstructibleWithParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = AreaOpeningFilter<SourceImageType,
            DestinationImageType>;
    using AreaSizeParameter = unsigned int;

    AssertThat<DummyFilter>::isConstructible(With<AreaSizeParameter>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(AreaOpeningFilterTest, AreaOpeningTests,
        TestData);
