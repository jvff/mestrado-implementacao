#ifndef MAX_TREE_NODE_REMOVAL_TEST_HPP
#define MAX_TREE_NODE_REMOVAL_TEST_HPP

#include <functional>

#include "MaxTreeTest.hpp"

class MaxTreeNodeRemovalTest : public MaxTreeTest<std::less<DummyType> > {
};

#endif
