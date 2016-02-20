#include "PixelNeighborhoodTest.hpp"

TEST_F(PixelNeighborhoodTest, classTemplateExists) {
    AssertThat<DummyPixelNeighborhood>::isClassOrStruct();
}

TEST_F(PixelNeighborhoodTest, isConstructibleWithParameters) {
    AssertThat<DummyPixelNeighborhood>::isConstructible(WithoutParameters());
}
