#ifndef MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP
#define MAX_TREE_LEVEL_NODE_REMOVAL_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeLevelTest.hpp"

template <typename LevelOrderComparator>
class MaxTreeLevelNodeRemovalTest
        : public MinMaxTreeLevelTest<LevelOrderComparator> {
};

#undef TEST_C
#define TEST_C(testName) \
    CREATE_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MaxTreeLevelNodeRemovalTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MaxTreeLevelNodeRemovalTest, testName)

#define CREATE_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MaxTreeLevelNodeRemovalTest, testName) \
        : public MaxTreeLevelNodeRemovalTest<TypeParameter> { \
private: \
    using SuperClass = MaxTreeLevelNodeRemovalTest<TypeParameter>; \
\
    using SuperClass::level; \
\
    using SuperClass::verifyNode; \
\
    virtual void TestBody(); \
}

#endif
