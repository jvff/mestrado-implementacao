#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"
#include "MaxTreeFilter.hpp"
#include "MaxTreeImage.hpp"
#include "MaxTreeImplementation.hpp"

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

TEST(MaxTreeFilterTest, isComplexFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
    using DestinationImageType = MaxTreeImage<InternalImageType>;
    using DummyMaxTreeFilter = MaxTreeFilter<SourceImageType,
            InternalImageType>;
    using ImplementationType = MaxTreeImplementation<SourceImageType,
            InternalImageType>;
    using ParentFilter = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;

    AssertThat<DummyMaxTreeFilter>::isSubClass(Of<ParentFilter>());
}
