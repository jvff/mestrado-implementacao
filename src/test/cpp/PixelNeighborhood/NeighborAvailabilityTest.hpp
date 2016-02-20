#ifndef NEIGHBOR_AVAILABILITY_TEST_HPP
#define NEIGHBOR_AVAILABILITY_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "PixelNeighborhood.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"


class PixelNeighborhoodNeighborAvailabilityTest : public ::testing::Test {
protected:
    PixelNeighborhood<DummyType> neighborhood;
    SimpleArrayImage<bool> maskImage;
    const Image<bool>& maskImageReference;

public:
    PixelNeighborhoodNeighborAvailabilityTest() : maskImage(3, 3),
            maskImageReference(maskImage) {
    }

    void SetUp() {
        maskImage = [] (unsigned int, unsigned int) {
            return false;
        };
    }
};

#define TEST_C(testName) \
    TEST_F(PixelNeighborhoodNeighborAvailabilityTest, testName)

#endif
