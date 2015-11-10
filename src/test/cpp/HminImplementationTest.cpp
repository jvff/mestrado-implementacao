#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "HminImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(HminImplementationTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementation = HminImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST(HminImplementationTest, isFilterImplementation) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = HminImplementation<SourceImageType,
            DestinationImageType>;
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}
