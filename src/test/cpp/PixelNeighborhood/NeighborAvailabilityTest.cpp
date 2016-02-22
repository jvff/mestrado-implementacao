#include "NeighborAvailabilityTest.hpp"

TEST_C(hasAvailableNeighborTest) {
    auto result = SimpleArrayImage<bool>(width, height);

    result = [&] (unsigned int x, unsigned int y) -> bool {
        return neighborhood.hasAvailableNeighbor(maskImageReference, x, y);
    };

    assertThat(result).isEqualTo(expectedResult);
}

INSTANTIATE_TEST_CASE_P(Test3By3Image,
        PixelNeighborhoodNeighborAvailabilityTest,
        ::testing::ValuesIn(PixelNeighborhoodNeighborAvailabilityTest
                ::generateParameters()));
