#ifndef MIN_MAX_TREE_NODE_TEST_HPP
#define MIN_MAX_TREE_NODE_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeNode.hpp"
#include "MinTreeNode.hpp"

#include "CustomTypedTestMacros.hpp"
#include "DummyTypes.hpp"

template <typename TypeParameter>
class MinMaxTreeNodeTest : public ::testing::Test {
};

#define TEST_C(testName) \
    CREATE_MIN_MAX_TREE_NODE_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MinMaxTreeNodeTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MinMaxTreeNodeTest, testName)

#define CREATE_MIN_MAX_TREE_NODE_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MinMaxTreeNodeTest, testName) \
        : public MinMaxTreeNodeTest<TypeParameter> { \
private: \
    using NodeType = TypeParameter; \
\
    virtual void TestBody(); \
}

#endif
