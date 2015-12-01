#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MaxTreeFilterTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DummyMaxTreeFilter = MaxTreeFilter<SourceImageType,
            InternalImageType>;

    AssertThat<DummyMaxTreeFilter>::isClassOrStruct();
}
