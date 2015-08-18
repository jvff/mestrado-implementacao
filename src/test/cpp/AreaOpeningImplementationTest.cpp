#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaOpeningImplementationTest, classTemplateExists) {
    using PixelType = DummyType;
    using ImageType = FakeImage<PixelType>;
    using ImplementationClass = AreaOpeningImplementation<PixelType,
            PixelType, ImageType>;

    AssertThat<ImplementationClass>::isClassOrStruct();
}

TEST(AreaOpeningImplementationTest, hasOptionalTemplateParameter) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplicitType = AreaOpeningImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType>;
    using ExplicitType = AreaOpeningImplementation<SourcePixelType,
            DestinationPixelType, DestinationImageType, SourceImageType>;

    AssertThat<ImplicitType>::isTheSame(As<ExplicitType>());
}
