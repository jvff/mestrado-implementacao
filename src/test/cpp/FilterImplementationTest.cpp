#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(FilterImplementationTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementationType = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyImplementationType>::isClassOrStruct();
}
