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
