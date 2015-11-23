#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaOpeningMaxTreeImplementationTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaOpeningMaxTreeImplementation<
            SourceImageType, DestinationImageType>;

    AssertThat<ImplementationClass>::isClassOrStruct();
}
