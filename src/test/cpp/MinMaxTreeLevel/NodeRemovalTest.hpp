#ifndef NODE_REMOVAL_TEST_HPP
#define NODE_REMOVAL_TEST_HPP

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
