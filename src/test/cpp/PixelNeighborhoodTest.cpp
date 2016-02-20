#include "PixelNeighborhoodTest.hpp"

TEST_F(PixelNeighborhoodTest, classTemplateExists) {
    AssertThat<DummyPixelNeighborhood>::isClassOrStruct();
}

TEST_F(PixelNeighborhoodTest, isConstructibleWithParameters) {
    AssertThat<DummyPixelNeighborhood>::isConstructible(WithoutParameters());
}

TEST_F(PixelNeighborhoodTest, canTestMaskImageIfThereIsAnAvailableNeighbor) {
    PixelNeighborhood<DummyType> neighborhood;

    auto maskImage = SimpleArrayImage<bool>(3, 3);
    const Image<bool>& maskImageReference = maskImage;

    maskImage = [] (unsigned int, unsigned int) {
        return false;
    };

    auto result = neighborhood.hasAvailableNeighbor(maskImageReference, 1, 1);

    assertThat(result).isEqualTo(true);
}
