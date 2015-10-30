#include <gtest/gtest.h>

#include "asserts.hpp"

#include "InversionFilter.hpp"
#include "InversionImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(InversionFilterTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyFilter = InversionFilter<Image<DummyType>, ImageType>;

    AssertThat<DummyFilter>::isClassOrStruct();
}

TEST(InversionFilterTest, isComplexFilter) {
    using SourceImageType = Image<DummyTypes<1> >;
    using DestinationImageType = FakeImage<DummyTypes<2> >;
    using ImplementationType = InversionImplementation<SourceImageType,
            DestinationImageType>;
    using FilterClass = InversionFilter<SourceImageType, DestinationImageType>;
    using ParentFilterClass = ComplexFilter<SourceImageType,
            DestinationImageType, ImplementationType>;

    AssertThat<FilterClass>::isSubClass(Of<ParentFilterClass>());
}
