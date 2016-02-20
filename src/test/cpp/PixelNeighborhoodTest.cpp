#include "PixelNeighborhoodTest.hpp"

TEST_F(PixelNeighborhoodTest, classTemplateExists) {
    AssertThat<DummyPixelNeighborhood>::isClassOrStruct();
}

TEST_F(PixelNeighborhoodTest, isConstructibleWithParameters) {
    AssertThat<DummyPixelNeighborhood>::isConstructible(WithoutParameters());
}

TEST_F(PixelNeighborhoodTest, canTestMaskImageIfThereIsAnAvailableNeighbor) {
    auto result = neighborhood.hasAvailableNeighbor(maskImageReference, 1, 1);

    assertThat(result).isEqualTo(true);
}

TEST_F(PixelNeighborhoodTest, hasNeighborAvailableIfOnlyNorthWasMarked) {
    maskImage.setPixel(1, 0, true);

    auto result = neighborhood.hasAvailableNeighbor(maskImageReference, 1, 1);

    assertThat(result).isEqualTo(true);
}
