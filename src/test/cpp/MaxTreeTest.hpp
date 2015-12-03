#ifndef MAX_TREE_TEST_HPP
#define MAX_TREE_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTree.hpp"

#include "DummyTypes.hpp"

class MaxTreeTest : public ::testing::Test {
protected:
    using DummyMaxTreeType = MaxTree<DummyType>;

    DummyMaxTreeType tree;
    const DummyMaxTreeType& constTree;

public:
    MaxTreeTest() : constTree(tree) {
    }
};

#endif
