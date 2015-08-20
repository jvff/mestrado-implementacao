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
