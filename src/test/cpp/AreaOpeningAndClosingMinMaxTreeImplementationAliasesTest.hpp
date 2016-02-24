#ifndef AREA_OPENING_AND_CLOSING_MIN_MAX_TREE_IMPLEMENTATION_ALIASES_TEST_HPP
#define AREA_OPENING_AND_CLOSING_MIN_MAX_TREE_IMPLEMENTATION_ALIASES_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "AreaOpeningMaxTreeImplementation.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class AreaOpeningAndClosingMinMaxTreeImplementationAliasesTest
        : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<0>;
    using DestinationPixelType = DummyTypes<1>;
    using SourceImageType = Image<SourcePixelType>;
    using DestinationImageType = FakeImage<DestinationPixelType>;
};

#define TEST_C(testName) \
        TEST_F(AreaOpeningAndClosingMinMaxTreeImplementationAliasesTest, \
                testName)

#endif
