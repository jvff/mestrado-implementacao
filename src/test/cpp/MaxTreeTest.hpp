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
        assertThat(node.level).isEqualTo(expectedLevel);
        assertThat(node.id).isEqualTo(expectedId);
    }
};

#endif
