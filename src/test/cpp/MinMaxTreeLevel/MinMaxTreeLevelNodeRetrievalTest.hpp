#ifndef MIN_MAX_TREE_LEVEL_NODE_RETRIEVAL_TEST_HPP
#define MIN_MAX_TREE_LEVEL_NODE_RETRIEVAL_TEST_HPP

#include <functional>
#include <limits>
#include <string>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeLevelTest.hpp"

template <typename LevelOrderComparator>
class MinMaxTreeLevelNodeRetrievalTest
        : public MinMaxTreeLevelTest<LevelOrderComparator> {
protected:
    using Statement = std::function<void()>;

protected:
    void verifyInexistentNodeException(Statement statement) {
        auto expectedMessage = "Attempt to retrieve inexistent node";

        try {
            statement();
            FAIL() << "Expected exception was not thrown";
        } catch (std::string exception) {
            assertThat(exception).isEqualTo(expectedMessage);
        }
    }
};

#undef TEST_C
#define TEST_C(testName) \
    CREATE_MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MinMaxTreeLevelNodeRetrievalTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MinMaxTreeLevelNodeRetrievalTest, testName)

#define CREATE_MIN_MAX_TREE_LEVEL_NODE_REMOVAL_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MinMaxTreeLevelNodeRetrievalTest, testName) \
        : public MinMaxTreeLevelNodeRetrievalTest<TypeParameter> { \
private: \
    using SuperClass = MinMaxTreeLevelNodeRetrievalTest<TypeParameter>; \
\
    using SuperClass::level; \
    using SuperClass::constLevel; \
\
    using SuperClass::verifyNode; \
    using SuperClass::verifyInexistentNodeException; \
\
    virtual void TestBody(); \
}

#endif
