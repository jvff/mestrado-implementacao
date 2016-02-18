#ifndef MIN_MAX_TREE_IMPLEMENTATION_ALIASES_TEST_HPP
#define MIN_MAX_TREE_IMPLEMENTATION_ALIASES_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class MinMaxTreeImplementationAliasesTest : public ::testing::Test {
protected:
    using SourcePixelType = DummyTypes<1>;
    using DestinationPixelType = DummyTypes<2>;
    using SourceImageType = Image<SourcePixelType>;
    using InternalImageType = FakeImage<DestinationPixelType>;
};

#endif
