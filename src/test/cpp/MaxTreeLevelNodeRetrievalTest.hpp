#ifndef MAX_TREE_LEVEL_NODE_RETRIEVAL_TEST_HPP
#define MAX_TREE_LEVEL_NODE_RETRIEVAL_TEST_HPP

#include <functional>
#include <limits>
#include <string>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevelTest.hpp"

class MaxTreeLevelNodeRetrievalTest
        : public MaxTreeLevelTest<std::less<DummyType> > {
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

#endif
