#ifndef MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP
#define MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeLevelTest.hpp"

class MaxTreeLevelNodeRemovalTest
        : public MinMaxTreeLevelTest<std::less<DummyType> > {
};

#endif
