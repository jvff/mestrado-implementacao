#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "HminFilter.hpp"
#include "HminImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(HminFilterTest, classTemplateExists) {
    using DestinationImageType = FakeImage<DummyType>;
    using DummyFilter = HminFilter<Image<DummyType>, DestinationImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(HminFilterTest, isComplexFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationType = HminImplementation<SourceImageType,
            DestinationImageType>;
    using FilterClass = HminFilter<SourceImageType, DestinationImageType>;
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilter>());
}

TEST(HminFilterTest, isConstructibleWithParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = HminFilter<SourceImageType, DestinationImageType>;
    using FeatureHeightParameter = const SourcePixelType&;

    AssertThat<DummyFilter>::isConstructible(With<FeatureHeightParameter>());
}
