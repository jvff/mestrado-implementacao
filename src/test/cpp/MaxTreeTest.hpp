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

    template <typename T, typename... RemainingParameterTypes>
    void verifyNodeChain(const T& startingLevel, unsigned int startingId,
            const RemainingParameterTypes&... remainingParameters) {
        auto node = tree.getNode(startingLevel, startingId);

        verifyNodeChain(node, startingLevel, startingId,
                remainingParameters...);
    }

    template <typename T, typename... RemainingParameterTypes>
    void verifyNodeChain(const MaxTreeNode<T>& node, const T& expectedLevel,
            unsigned int expectedId,
            const RemainingParameterTypes&... remainingParameters) {
        auto& parent = *node.parent;

        verifyNode(node, expectedLevel, expectedId);

        verifyNodeChain(parent, remainingParameters...);
    }

    template <typename T>
    void verifyNodeChain(const MaxTreeNode<T>& node, const T& expectedLevel,
            unsigned int expectedId) {
        auto hasParent = (bool)node.parent;

        verifyNode(node, expectedLevel, expectedId);

        assertThat(hasParent).isEqualTo(false);
    }

    template <typename T>
    void verifyNode(const MaxTreeNode<T>& node, const T& expectedLevel,
            unsigned int expectedId) {
        assertThat(node.getLevel()).isEqualTo(expectedLevel);
        assertThat(node.getId()).isEqualTo(expectedId);
    }
};

#endif
