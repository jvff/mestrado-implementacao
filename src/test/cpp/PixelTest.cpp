#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Pixel.hpp"

#include "DummyTypes.hpp"

TEST(PixelTest, structTemplateExists) {
    AssertThat<Pixel<DummyType> >::isClassOrStruct();
}
