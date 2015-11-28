#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(MaxTreeImplementationTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DummyImplementationType = MaxTreeImplementation<SourceImageType,
            InternalImageType>;

    AssertThat<DummyImplementationType>::isClassOrStruct();
}
