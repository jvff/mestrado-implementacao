#ifndef MAX_TREE_NODE_COMPARISON_TEST_HPP
#define MAX_TREE_NODE_COMPARISON_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

class MaxTreeNodeComparisonTest : public ::testing::Test {
protected:
    using NodeType = MaxTreeNode<DummyType>;
    using NodePointer = std::shared_ptr<NodeType>;

protected:
    NodeType makeNode(DummyType level, unsigned int id) {
        return NodeType(level, id);
    }

    NodeType makeNode(NodePointer parent, DummyType level, unsigned int id) {
        return NodeType(parent, level, id);
    }

    template <typename... RemainingParameterTypes>
    NodeType makeNodeChain(DummyType level, unsigned int id,
            RemainingParameterTypes... remainingParameters) {
        auto rootNode = std::make_shared<NodeType>(level, id);

        return makeNodeChain(rootNode, remainingParameters...);
    }

    template <typename... RemainingParameterTypes>
    NodeType makeNodeChain(NodePointer parent, DummyType level, unsigned int id,
            RemainingParameterTypes... remainingParameters) {
        auto node = std::make_shared<NodeType>(parent, level, id);

        return makeNodeChain(node, remainingParameters...);
    }

    NodeType makeNodeChain(NodePointer parent, DummyType level,
            unsigned int id) {
        return makeNode(parent, level, id);
    }
};

#endif
