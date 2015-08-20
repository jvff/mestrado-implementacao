#include <gtest/gtest.h>

#include "asserts.hpp"

#include "SimpleFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(SimpleFilterTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilterType = SimpleFilter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilterType>::isClassOrStruct();
}

TEST(SimpleFilterTest, isSubClassOfFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = SimpleFilter<SourceImageType, DestinationImageType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}
