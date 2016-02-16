#ifndef NODE_VERIFICATION_HELPER_HPP
#define NODE_VERIFICATION_HELPER_HPP

#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeNode.hpp"

#include "DummyTypes.hpp"

template <typename PixelType, typename LevelOrderComparator>
class NodeVerificationHelper {
protected:
    using NodeType = MinMaxTreeNode<PixelType, LevelOrderComparator>;
    using NodePointer = std::shared_ptr<NodeType>;

protected:
    NodePointer makeNode(unsigned int id, PixelType level) {
        return std::make_shared<NodeType>(level, id);
    }

    NodePointer makeNode(unsigned int id, PixelType level, NodePointer parent) {
        return std::make_shared<NodeType>(parent, level, id);
    }

    template <typename... RemainingParameterTypes>
    void verifyNode(NodePointer nodePointer,
            const RemainingParameterTypes&... remainingParameters) {
        verifyNode(*nodePointer, remainingParameters...);
    }

    template <typename... RemainingParameterTypes>
    void verifyNode(const NodeType& node, PixelType level, unsigned int id,
            const RemainingParameterTypes&... remainingParameters) {
        verifyNodeData(node, level, id);
        verifyNodeIsNotRoot(node);

        if (node.hasParent())
            verifyNode(node.getParent(), remainingParameters...);
    }

    void verifyNode(const NodeType& node, PixelType level, unsigned int id) {
        verifyNodeData(node, level, id);
        verifyNodeIsRoot(node);
    }

    void verifyNodeIsRoot(const NodeType& node) {
        assertThat(node.hasParent()).isEqualTo(false);
    }

    void verifyNodeIsNotRoot(const NodeType& node) {
        assertThat(node.hasParent()).isEqualTo(true);
    }

    void verifyNode(const NodeType& node,
            const NodePointer& expectedNodePointer) {
        verifyNode(node, *expectedNodePointer);
    }

    void verifyNode(const NodeType& node, const NodeType& expectedNode) {
        verifyNodeData(node, expectedNode);
        verifyNodeParents(node, expectedNode);
    }

    void verifyNodeData(const NodeType& node, PixelType level,
            unsigned int id) {
        assertThat(node.getLevel()).isEqualTo(level);
        assertThat(node.getId()).isEqualTo(id);
    }

    void verifyNodeData(const NodeType& node, const NodeType& expectedNode) {
        assertThat(node.getLevel()).isEqualTo(expectedNode.getLevel());
        assertThat(node.getId()).isEqualTo(expectedNode.getId());
    }

private:
    void verifyNodeParents(const NodeType& node, const NodeType& expectedNode) {
        assertThat(node.hasParent()).isEqualTo(expectedNode.hasParent());

        if (node.hasParent() && expectedNode.hasParent())
            safelyVerifyNodeParents(node, expectedNode);
    }

    void safelyVerifyNodeParents(const NodeType& node,
            const NodeType& expectedNode) {
        auto& parent = node.getParent();
        auto& expectedParent = expectedNode.getParent();

        verifyNodeData(parent, expectedParent);
        verifyNodeParents(parent, expectedParent);
    }
};

#endif
