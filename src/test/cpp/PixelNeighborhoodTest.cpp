#include <gtest/gtest.h>

#include "asserts.hpp"

#include "PixelNeighborhood.hpp"

#include "DummyTypes.hpp"

TEST(PixelNeighborhoodTest, classTemplateExists) {
    using DummyPixelNeighborhood = PixelNeighborhood<DummyType>;

    AssertThat<DummyPixelNeighborhood>::isClassOrStruct();
}
