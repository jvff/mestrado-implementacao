#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "BinarizationFilter.hpp"

#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

#define TEST_C(testName) \
        TEST(BinarizationFilterBasicTests, testName)

TEST_C(classIsntAbstractAndConstructorHasParameter) {
    using DummyBinarizationFilter = BinarizationFilter<Image<DummyType>,
            FakeImage<bool> >;
    using ThresholdParameter = const DummyType&;

    AssertThat<DummyBinarizationFilter>::isConstructible(
            With<ThresholdParameter>());
}

TEST_C(hasComparatorTemplateParameter) {
    using DummyBinarizationFilter = BinarizationFilter<Image<DummyType>,
            FakeImage<bool>, std::less>;
    using ThresholdParameter = const DummyType&;

    AssertThat<DummyBinarizationFilter>::isConstructible(
            With<ThresholdParameter>());
}

TEST_C(defaultComparatorIsGreaterThan) {
    using FilterWithDefaultComparator = BinarizationFilter<Image<DummyType>,
            FakeImage<bool> >;
    using ExpectedFilterType = BinarizationFilter<Image<DummyType>,
            FakeImage<bool>, std::greater>;

    AssertThat<FilterWithDefaultComparator>::isTheSame(
            As<ExpectedFilterType>());
}

TEST_C(classIsSimpleFilter) {
    using ParentFilter = SimpleFilter<Image<DummyType>, FakeImage<bool> >;
    using FilterType = BinarizationFilter<Image<DummyType>, FakeImage<bool> >;

    AssertThat<FilterType>::isSubClass(Of<ParentFilter>());
}
