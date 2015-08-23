#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ComplexFilter.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(ComplexFilterTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using ImplementationType = DummyTypes<3>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyFilterType = ComplexFilter<SourceImageType,
            DestinationImageType, ImplementationType>;

    AssertThat<DummyFilterType>::isClassOrStruct();
}

TEST(ComplexFilterTest, isSubClassOfFilter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using ImplementationType = DummyTypes<3>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using SubClass = ComplexFilter<SourceImageType, DestinationImageType,
            ImplementationType>;
    using SuperClass = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

    AssertThat<SubClass>::isSubClass(Of<SuperClass>());
}
