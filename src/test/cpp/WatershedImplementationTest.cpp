#include "WatershedImplementationTest.hpp"
#include "WatershedTests.hpp"

TEST_F(WatershedImplementationTest, classTemplateExists) {
    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST_F(WatershedImplementationTest, isConstructible) {
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(
            With<SourceImageParameter, DestinationImageParameter>());
}

TEST_F(WatershedImplementationTest, isFilterImplementation) {
    using SubClass = DummyImplementation;
    using SuperClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}

INSTANTIATE_COMPLEX_FILTER_TEST_CASE(WatershedImplementationTest,
        WatershedTests, TestData);
