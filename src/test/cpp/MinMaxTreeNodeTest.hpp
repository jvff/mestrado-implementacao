#ifndef MIN_MAX_TREE_NODE_TEST_HPP
#define MIN_MAX_TREE_NODE_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"
#include "MinTreeNode.hpp"

#include "DummyTypes.hpp"

template <typename TypeParameter>
class MinMaxTreeNodeTest : public ::testing::Test {
};

#define MIN_MAX_TREE_NODE_TEST(testName) \
    CREATE_MIN_MAX_TREE_NODE_TEST_CLASS(testName); \
    REGISTER_MIN_MAX_TREE_NODE_TEST_CASE(testName); \
    START_MIN_MAX_TREE_NODE_TEST_BODY(testName)

#define CREATE_MIN_MAX_TREE_NODE_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MinMaxTreeNodeTest, testName) \
        : public MinMaxTreeNodeTest<TypeParameter> { \
private: \
    using NodeType = TypeParameter; \
\
    virtual void TestBody(); \
}

#define REGISTER_MIN_MAX_TREE_NODE_TEST_CASE(testName) \
    bool gtest_MinMaxTreeNodeTest_##testName##_registered_ \
        GTEST_ATTRIBUTE_UNUSED_ = ::testing::internal::TypeParameterizedTest< \
            MinMaxTreeNodeTest, ::testing::internal::TemplateSel< \
                GTEST_TEST_CLASS_NAME_(MinMaxTreeNodeTest, testName)>, \
            GTEST_TYPE_PARAMS_(MinMaxTreeNodeTest)>::Register(\
                "", "MinMaxTreeNodeTest", #testName, 0) \

#define START_MIN_MAX_TREE_NODE_TEST_BODY(testName) \
template <typename TypeParameter> \
void GTEST_TEST_CLASS_NAME_(MinMaxTreeNodeTest, testName)<TypeParameter> \
        ::TestBody()

#endif
