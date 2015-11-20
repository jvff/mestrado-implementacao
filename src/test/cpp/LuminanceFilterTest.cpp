#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Filter.hpp"
#include "LuminanceFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(LuminanceFilter, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilter = LuminanceFilter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(LuminanceFilter, isSubClassOfFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilterClass = LuminanceFilter<SourceImageType,
            DestinationImageType>;
    using ParentFilterClass = Filter<SourceImageType, DestinationImageType>;

    AssertThat<DummyFilterClass>::isSubClass(Of<ParentFilterClass>());
}
