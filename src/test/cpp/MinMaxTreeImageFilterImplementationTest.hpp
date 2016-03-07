#ifndef MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP
#define MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "MinMaxTreeImage.hpp"
#include "MinMaxTreeImageFilterImplementation.hpp"

#include "DummyTypes.hpp"
#include "FakeMinMaxTreeImageFilterImplementation.hpp"
#include "SimpleArrayImage.hpp"

class MinMaxTreeImageFilterImplementationTest : public ::testing::Test {
protected:
    using PixelType = DummyType;
    using LevelOrderComparator = std::greater<PixelType>;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using ImageType = MinMaxTreeImage<InternalImageType, LevelOrderComparator>;
    using ImplementationType = MinMaxTreeImageFilterImplementation<
            InternalImageType, LevelOrderComparator>;
    using FakeImplementationType = FakeMinMaxTreeImageFilterImplementation<
            InternalImageType, LevelOrderComparator>;
};

#endif
