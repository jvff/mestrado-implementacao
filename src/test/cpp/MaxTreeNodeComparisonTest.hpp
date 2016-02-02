#ifndef MAX_TREE_NODE_COMPARISON_TEST_HPP
#define MAX_TREE_NODE_COMPARISON_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"

#include "DummyTypes.hpp"

template <typename TypeParameter>
class MaxTreeNodeComparisonTest : public ::testing::Test {
protected:
    using NodeType = TypeParameter;
    using NodePointer = std::shared_ptr<NodeType>;

protected:
    NodeType makeNode(DummyType level, unsigned int id) {
        return NodeType(level, id);
    }

    NodeType makeNode(NodePointer parent, DummyType level, unsigned int id) {
        return NodeType(parent, level, id);
    }

    NodePointer makeNodePointer(DummyType level, unsigned int id) {
        return std::make_shared<NodeType>(level, id);
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

#define TEST_C(testName) \
    CREATE_MAX_TREE_NODE_COMPARISON_TEST_CLASS(testName); \
    REGISTER_MAX_TREE_NODE_COMPARISON_TEST_CASE(testName); \
    START_MAX_TREE_NODE_COMPARISON_TEST_BODY(testName)

#define CREATE_MAX_TREE_NODE_COMPARISON_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MaxTreeNodeComparisonTest, testName) \
        : public MaxTreeNodeComparisonTest<TypeParameter> { \
private: \
    using SuperClass = MaxTreeNodeComparisonTest<TypeParameter>; \
\
    using SuperClass::makeNode; \
    using SuperClass::makeNodePointer; \
    using SuperClass::makeNodeChain; \
\
    virtual void TestBody(); \
}

#define REGISTER_MAX_TREE_NODE_COMPARISON_TEST_CASE(testName) \
    bool gtest_MaxTreeNodeTest_##testName##_registered_ \
        GTEST_ATTRIBUTE_UNUSED_ = ::testing::internal::TypeParameterizedTest< \
            MaxTreeNodeComparisonTest, ::testing::internal::TemplateSel< \
                GTEST_TEST_CLASS_NAME_(MaxTreeNodeComparisonTest, testName)>, \
            GTEST_TYPE_PARAMS_(MaxTreeNodeComparisonTest)>::Register(\
                "", "MaxTreeNodeComparisonTest", #testName, 0) \

#define START_MAX_TREE_NODE_COMPARISON_TEST_BODY(testName) \
template <typename TypeParameter> \
void GTEST_TEST_CLASS_NAME_(MaxTreeNodeComparisonTest, testName)<TypeParameter> \
        ::TestBody()

#endif
