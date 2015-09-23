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
