#ifndef MAX_TREE_LEVEL_TEST_HPP
#define MAX_TREE_LEVEL_TEST_HPP

#include <functional>
#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevel.hpp"

#include "CustomTypedTestMacros.hpp"
#include "DummyTypes.hpp"

template <typename TypeParameter>
class MaxTreeLevelTest : public ::testing::Test {
protected:
    using LevelOrderComparator = TypeParameter;
    using DummyMaxTreeLevel = MinMaxTreeLevel<DummyType, LevelOrderComparator>;
    using NodeType = MinMaxTreeNode<DummyType, LevelOrderComparator>;
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
        verifyNodeData(node, expectedId);

        assertThat(node.hasParent()).isEqualTo(false);
    }

    void verifyNode(NodePointer nodePointer, unsigned int expectedId,
            const DummyType& expectedLevel) {
        verifyNode(*nodePointer, expectedId, expectedLevel);
    }

    void verifyNode(const NodeType& node, unsigned int expectedId,
            const DummyType& expectedLevel) {
        verifyNodeData(node, expectedId, expectedLevel);

        assertThat(node.hasParent()).isEqualTo(false);
    }

    void verifyNode(NodePointer nodePointer, unsigned int expectedId,
            NodePointer expectedParent) {
        verifyNode(*nodePointer, expectedId, expectedParent);
    }

    void verifyNode(const NodeType& node, unsigned int expectedId,
            NodePointer expectedParent) {
        auto expectedParentId = expectedParent->getId();
        auto expectedParentLevel = expectedParent->getLevel();

        verifyNodeData(node, expectedId);

        assertThat(node.hasParent()).isEqualTo(true);

        verifyNode(node.getParent(), expectedParentId, expectedParentLevel);
    }

    void verifyNodeData(const NodeType& node, unsigned int expectedId) {
        verifyNodeData(node, expectedId, levelHeight);
    }

    void verifyNodeData(const NodeType& node, unsigned int expectedId,
            const DummyType& expectedLevel) {
        assertThat(node.getLevel()).isEqualTo(expectedLevel);
        assertThat(node.getId()).isEqualTo(expectedId);
    }
};

#define TEST_C(testName) \
    CREATE_MAX_TREE_LEVEL_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MaxTreeLevelTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MaxTreeLevelTest, testName)

#define CREATE_MAX_TREE_LEVEL_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MaxTreeLevelTest, testName) \
        : public MaxTreeLevelTest<TypeParameter> { \
private: \
    using SuperClass = MaxTreeLevelTest<TypeParameter>; \
    using DummyMaxTreeLevel = typename SuperClass::DummyMaxTreeLevel; \
    using NodeType = typename SuperClass::NodeType; \
\
    using SuperClass::levelHeight; \
    using SuperClass::level; \
    using SuperClass::constLevel; \
\
    using SuperClass::verifyNode; \
\
    virtual void TestBody(); \
}

#endif
