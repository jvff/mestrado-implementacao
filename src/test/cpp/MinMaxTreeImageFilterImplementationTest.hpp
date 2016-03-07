#ifndef MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP
#define MIN_MAX_TREE_IMAGE_FILTER_IMPLEMENTATION_TEST_HPP

#include <set>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "FilterImplementation.hpp"
#include "MinMaxTreeImage.hpp"
#include "MinMaxTreeImageFilterImplementation.hpp"
#include "MinMaxTreeNode.hpp"

#include "DummyTypes.hpp"
#include "FakeMinMaxTreeImageFilterImplementation.hpp"
#include "NodeVerificationHelper.hpp"
#include "SimpleArrayImage.hpp"

class MinMaxTreeImageFilterImplementationTest : public ::testing::Test,
        protected NodeVerificationHelper<DummyType, std::greater<DummyType> > {
protected:
    using PixelType = DummyType;
    using LevelOrderComparator = std::greater<PixelType>;
    using NodeType = MinMaxTreeNode<PixelType, LevelOrderComparator>;
    using InternalImageType = SimpleArrayImage<PixelType>;
    using ImageType = MinMaxTreeImage<InternalImageType, LevelOrderComparator>;
    using ImplementationType = MinMaxTreeImageFilterImplementation<
            InternalImageType, LevelOrderComparator>;
    using FakeImplementationType = FakeMinMaxTreeImageFilterImplementation<
            InternalImageType, LevelOrderComparator>;
};

#endif
