#ifndef MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP
#define MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeLevelTest.hpp"

template <typename LevelOrderComparator>
class MinMaxTreeLevelNodeRemovalTest
        : public MinMaxTreeLevelTest<LevelOrderComparator> {
};

#undef TEST_C
#define TEST_C(testName) \
    CREATE_MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MinMaxTreeLevelNodeRemovalTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MinMaxTreeLevelNodeRemovalTest, testName)

#define CREATE_MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MinMaxTreeLevelNodeRemovalTest, testName) \
        : public MinMaxTreeLevelNodeRemovalTest<TypeParameter> { \
private: \
    using SuperClass = MinMaxTreeLevelNodeRemovalTest<TypeParameter>; \
\
    using SuperClass::level; \
\
    using SuperClass::verifyNode; \
\
    virtual void TestBody(); \
}

#endif
