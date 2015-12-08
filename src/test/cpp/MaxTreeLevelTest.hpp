#ifndef MAX_TREE_LEVEL_TEST_HPP
#define MAX_TREE_LEVEL_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevel.hpp"

#include "DummyTypes.hpp"

class MaxTreeLevelTest : public ::testing::Test {
protected:
    using DummyMaxTreeLevel = MaxTreeLevel<DummyType>;
    using NodeType = MaxTreeNode<DummyType>;
    using NodePointer = std::shared_ptr<NodeType>;

    DummyType levelHeight;
    DummyMaxTreeLevel level;
    const DummyMaxTreeLevel& constLevel;

public:
    MaxTreeLevelTest() : levelHeight(DummyType{ 201 }), level(levelHeight),
            constLevel(level) {
    }

protected:
    void verifyNode(NodePointer nodePointer, unsigned int expectedId) {
        verifyNode(*nodePointer, expectedId);
    }

    void verifyNode(const NodeType& node, unsigned int expectedId) {
        assertThat(node.getLevel()).isEqualTo(levelHeight);
        assertThat(node.getId()).isEqualTo(expectedId);
    }
};

#endif
