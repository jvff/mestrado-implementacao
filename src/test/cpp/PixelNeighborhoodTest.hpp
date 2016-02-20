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
};

#endif
