#include <gtest/gtest.h>

#include "asserts.hpp"

#include "WatershedImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

TEST(WatershedImplementationTest, classTemplateExists) {
    using ImageType = FakeImage<DummyType>;
    using DummyImplementation = WatershedImplementation<DummyType, DummyType,
            ImageType>;

    AssertThat<DummyImplementation>::isClassOrStruct();
}
