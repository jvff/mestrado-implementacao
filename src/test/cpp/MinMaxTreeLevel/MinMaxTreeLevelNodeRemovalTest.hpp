#ifndef MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP
#define MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeLevelTest.hpp"

template <typename LevelOrderComparator>
class MinMaxTreeLevelNodeRemovalTest
        : public MinMaxTreeLevelTest<LevelOrderComparator> {
};

#undef TEST_FIXTURE_NAME
#define TEST_FIXTURE_NAME MinMaxTreeLevelNodeRemovalTest

#endif
