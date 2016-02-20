#include "NeighborAvailabilityTest.hpp"

TEST_C(canTestMaskImageIfThereIsAnAvailableNeighbor) {
    auto result = neighborhood.hasAvailableNeighbor(maskImageReference, 1, 1);

    assertThat(result).isEqualTo(true);
}

TEST_C(hasNeighborAvailableIfOnlyNorthWasMarked) {
    maskImage.setPixel(1, 0, true);

    auto result = neighborhood.hasAvailableNeighbor(maskImageReference, 1, 1);

    assertThat(result).isEqualTo(true);
}
