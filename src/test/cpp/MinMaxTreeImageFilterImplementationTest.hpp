#ifndef MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP
#define MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeImageFilterImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class MinMaxTreeImageFilterImplementationTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using InternalImageType = FakeImage<PixelType>;
    using LevelOrderComparator = std::greater<PixelType>;
    using ImplementationType = MinMaxTreeImageFilterImplementation<
            InternalImageType, LevelOrderComparator>;
};

#endif
