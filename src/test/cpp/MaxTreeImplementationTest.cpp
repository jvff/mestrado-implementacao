#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "MaxTreeImage.hpp"
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

TEST(MaxTreeImplementationTest, isFilterImplementation) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DestinationImageType = MaxTreeImage<InternalImageType>;
    using DummyImplementationType = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
    using ParentClass = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyImplementationType>::isSubClass(Of<ParentClass>());
}
