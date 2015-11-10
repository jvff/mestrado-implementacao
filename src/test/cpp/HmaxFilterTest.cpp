#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "HmaxFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(HmaxFilterTest, classTemplateExists) {
    using DestinationImageType = FakeImage<DummyType>;
    using DummyFilter = HmaxFilter<Image<DummyType>, DestinationImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(HmaxFilterTest, isFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using FilterClass = HmaxFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = Filter<SourceImageType, DestinationImageType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilter>());
}

TEST(HmaxFilterTest, isConstructibleWithParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = HmaxFilter<SourceImageType, DestinationImageType>;
    using FeatureHeightParameter = const SourcePixelType&;

    AssertThat<DummyFilter>::isConstructible(With<FeatureHeightParameter>());
}
