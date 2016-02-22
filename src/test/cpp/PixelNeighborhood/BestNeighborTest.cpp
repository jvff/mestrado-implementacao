#include "BestNeighborTest.hpp"

TEST_C(getBestNeighborTest) {
    auto result = SimpleArrayImage<Pixel<DummyType> >(width, height);

    result = [&] (unsigned int x, unsigned int y) -> Pixel<DummyType> {
        return neighborhood.getBestNeighbor(sourceImageReference,
                maskImageReference, x, y, comparator);
    };

    assertThat(result).isEqualTo(expectedResult);
}

INSTANTIATE_TEST_CASE_P(Test3By3Image,
        PixelNeighborhoodBestNeighborTest,
        ::testing::ValuesIn(PixelNeighborhoodBestNeighborTest
                ::generateParameters()));
