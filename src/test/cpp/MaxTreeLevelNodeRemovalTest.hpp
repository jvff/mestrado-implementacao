#ifndef MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP
#define MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevelTest.hpp"

class MaxTreeLevelNodeRemovalTest
        : public MaxTreeLevelTest<std::less<DummyType> > {
};

#endif
