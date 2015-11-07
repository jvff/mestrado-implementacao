#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaClosingImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(AreaClosingImplementationTest, classTemplateExists) {
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
    using ImplementationClass = AreaClosingImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isClassOrStruct();
}
