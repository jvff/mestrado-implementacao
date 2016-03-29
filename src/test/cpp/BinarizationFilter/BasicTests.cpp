#include "BinarizationFilterTest.hpp"

TEST_C(BasicTests, classIsntAbstractAndConstructorHasParameter) {
    using DummyBinarizationFilter = BinarizationFilter<Image<DummyType>,
            FakeImage<bool> >;
    using ThresholdParameter = const DummyType&;

    AssertThat<DummyBinarizationFilter>::isConstructible(
            With<ThresholdParameter>());
}

TEST_C(BasicTests, hasComparatorTemplateParameter) {
    using DummyBinarizationFilter = BinarizationFilter<Image<DummyType>,
            FakeImage<bool>, std::less>;
    using ThresholdParameter = const DummyType&;

    AssertThat<DummyBinarizationFilter>::isConstructible(
            With<ThresholdParameter>());
}

TEST_C(BasicTests, defaultComparatorIsGreaterThan) {
    using FilterWithDefaultComparator = BinarizationFilter<Image<DummyType>,
            FakeImage<bool> >;
    using ExpectedFilterType = BinarizationFilter<Image<DummyType>,
            FakeImage<bool>, std::greater>;

    AssertThat<FilterWithDefaultComparator>::isTheSame(
            As<ExpectedFilterType>());
}

TEST_C(BasicTests, classIsSimpleFilter) {
    using ParentFilter = SimpleFilter<Image<DummyType>, FakeImage<bool> >;
    using FilterType = BinarizationFilter<Image<DummyType>, FakeImage<bool> >;

    AssertThat<FilterType>::isSubClass(Of<ParentFilter>());
}
