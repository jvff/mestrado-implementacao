#include <gtest/gtest.h>

#include "asserts.hpp"

#include "InversionImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(InversionImplementationTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyImplementation = InversionImplementation<Image<DummyType>,
            ImageType>;

    AssertThat<DummyImplementation>::isClassOrStruct();
}

TEST(InversionImplementationTest, isFilterImplementation) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationType = InversionImplementation<SourceImageType,
            DestinationImageType>;
    using FilterImplementationType = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationType>::isSubClass(Of<FilterImplementationType>());
}

TEST(InversionImplementationTest, canBeConstructedWithoutExtraParameters) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using DummyImplementation = InversionImplementation<SourceImageType,
            DestinationImageType>;
    using SourceImageParameter = const SourceImageType&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<DummyImplementation>::isConstructible(With<SourceImageParameter,
            DestinationImageParameter>());
}
