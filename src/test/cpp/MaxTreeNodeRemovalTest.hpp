#ifndef MAX_TREE_NODE_REMOVAL_TEST_HPP
#define MAX_TREE_NODE_REMOVAL_TEST_HPP

#include <functional>

#include "MinMaxTreeTest.hpp"

class MaxTreeNodeRemovalTest : public MinMaxTreeTest<std::less<DummyType> > {
};

#endif
