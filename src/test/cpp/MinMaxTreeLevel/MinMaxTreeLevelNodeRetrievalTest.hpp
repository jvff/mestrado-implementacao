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

#undef TEST_FIXTURE_NAME
#define TEST_FIXTURE_NAME MinMaxTreeLevelNodeRetrievalTest

#undef EXTRA_FIXTURE_MEMBERS
#define EXTRA_FIXTURE_MEMBERS \
    using SuperClass::verifyInexistentNodeException;

#endif
