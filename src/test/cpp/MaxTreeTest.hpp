#ifndef MAX_TREE_TEST_HPP
#define MAX_TREE_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTree.hpp"

#include "CustomTypedTestMacros.hpp"
#include "DummyTypes.hpp"

template <typename TypeParameter>
class MaxTreeTest : public ::testing::Test {
protected:
    using DummyMaxTreeType = MaxTree<DummyType>;

    DummyMaxTreeType tree;
    const DummyMaxTreeType& constTree;

public:
    MaxTreeTest() : constTree(tree) {
    }

    template <typename T, typename... RemainingParameterTypes>
    void verifyNodeChain(const T& startingLevel, unsigned int startingId,
            const RemainingParameterTypes&... remainingParameters) {
        const auto& node = tree.getNode(startingLevel, startingId);

        verifyNodeChain(node, startingLevel, startingId,
                remainingParameters...);
    }

    template <typename T, typename... RemainingParameterTypes>
    void verifyNodeChain(const MaxTreeNode<T>& node, const T& expectedLevel,
            unsigned int expectedId,
            const RemainingParameterTypes&... remainingParameters) {
        const auto& parent = node.getParent();

        verifyNode(node, expectedLevel, expectedId);

        verifyNodeChain(parent, remainingParameters...);
    }

    template <typename T>
    void verifyNodeChain(const MaxTreeNode<T>& node, const T& expectedLevel,
            unsigned int expectedId) {
        verifyNode(node, expectedLevel, expectedId);

        assertThat(node.hasParent()).isEqualTo(false);
    }

    template <typename T>
    void verifyNode(const MaxTreeNode<T>& node, const T& expectedLevel,
            unsigned int expectedId) {
        assertThat(node.getLevel()).isEqualTo(expectedLevel);
        assertThat(node.getId()).isEqualTo(expectedId);
    }
};

#define TEST_C(testName) \
    CREATE_MIN_MAX_TREE_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MaxTreeTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MaxTreeTest, testName)

#define CREATE_MIN_MAX_TREE_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MaxTreeTest, testName) \
        : public MaxTreeTest<TypeParameter> { \
private: \
    using SuperClass = MaxTreeTest<TypeParameter>; \
    using DummyMaxTreeType = typename SuperClass::DummyMaxTreeType; \
\
    using SuperClass::tree; \
    using SuperClass::constTree; \
\
    using SuperClass::verifyNodeChain; \
\
    virtual void TestBody(); \
}

#endif
