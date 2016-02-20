#ifndef BASIC_TESTS_HPP
#define BASIC_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "PixelNeighborhood.hpp"

#include "../DummyTypes.hpp"

class PixelNeighborhoodBasicTests : public ::testing::Test {
protected:
    using DummyPixelNeighborhood = PixelNeighborhood<DummyType>;
};

#define TEST_C(testName) \
    TEST_F(PixelNeighborhoodBasicTests, testName)

#endif
