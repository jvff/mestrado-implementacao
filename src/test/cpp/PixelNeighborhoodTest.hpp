#ifndef PIXEL_NEIGHBORHOOD_TEST_HPP
#define PIXEL_NEIGHBORHOOD_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"
#include "PixelNeighborhood.hpp"
#include "SimpleArrayImage.hpp"

#include "DummyTypes.hpp"

class PixelNeighborhoodTest : public ::testing::Test {
protected:
    using DummyPixelNeighborhood = PixelNeighborhood<DummyType>;

    DummyPixelNeighborhood neighborhood;
    SimpleArrayImage<bool> maskImage;
    const Image<bool>& maskImageReference;

public:
    PixelNeighborhoodTest() : maskImage(3, 3), maskImageReference(maskImage) {
    }

    void SetUp() {
        maskImage = [] (unsigned int, unsigned int) {
            return false;
        };
    }
};

#endif
