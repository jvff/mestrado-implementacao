#ifndef MIN_MAX_TREE_TEST_HPP
#define MIN_MAX_TREE_TEST_HPP

#include <functional>
#include <initializer_list>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTree.hpp"
#include "MaxTree.hpp"

#include "CustomTypedTestMacros.hpp"
#include "DummyTypes.hpp"

template <typename TypeParameter>
class MinMaxTreeTest : public ::testing::Test {
protected:
    using LevelOrderComparator = TypeParameter;
    using NodeType = MinMaxTreeNode<DummyType, LevelOrderComparator>;
    using DummyMinMaxTreeType = MinMaxTree<DummyType, LevelOrderComparator>;

    DummyMinMaxTreeType tree;
    const DummyMinMaxTreeType& constTree;

public:
    MinMaxTreeTest() : constTree(tree) {
    }

    std::vector<DummyType> makeLevelHeights(
            std::initializer_list<int> heightValues) {
        std::vector<DummyType> heightsToSort;

        for (auto height : heightValues)
            heightsToSort.push_back(DummyType{ height });

        return sortLevelHeights(heightsToSort);
    }

    template <typename T, typename... RemainingParameterTypes>
    void verifyNodeChain(const T& startingLevel, unsigned int startingId,
            const RemainingParameterTypes&... remainingParameters) {
        const auto& node = tree.getNode(startingLevel, startingId);

        verifyNodeChain(node, startingLevel, startingId,
                remainingParameters...);
    }

    template <typename T, typename... RemainingParameterTypes>
    void verifyNodeChain(const NodeType& node, const T& expectedLevel,
            unsigned int expectedId,
            const RemainingParameterTypes&... remainingParameters) {
        verifyNode(node, expectedLevel, expectedId);

        assertThat(node.hasParent()).isEqualTo(true);

        if (node.hasParent()) {
            const auto& parent = node.getParent();

            verifyNodeChain(parent, remainingParameters...);
        }
    }

    template <typename T>
    void verifyNodeChain(const NodeType& node, const T& expectedLevel,
            unsigned int expectedId) {
        verifyNode(node, expectedLevel, expectedId);

        assertThat(node.hasParent()).isEqualTo(false);
    }

    template <typename T>
    void verifyNode(const NodeType& node, const T& expectedLevel,
            unsigned int expectedId) {
        assertThat(node.getLevel()).isEqualTo(expectedLevel);
        assertThat(node.getId()).isEqualTo(expectedId);
    }

private:
    std::vector<DummyType> sortLevelHeights(std::vector<DummyType>& heights) {
        LevelOrderComparator comparator;

        std::sort(heights.begin(), heights.end(), comparator);

        return heights;
    }
};

#define TEST_C(testFixture, testName) \
    CREATE_MIN_MAX_TREE_TEST_CLASS(testFixture, testName); \
    REGISTER_CUSTOM_TYPED_TEST(testFixture, testName); \
    START_CUSTOM_TYPED_TEST_BODY(testFixture, testName)

#define CREATE_MIN_MAX_TREE_TEST_CLASS(testFixture, testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(testFixture, testName) \
        : public testFixture<TypeParameter> { \
private: \
    using SuperClass = testFixture<TypeParameter>; \
    using DummyMinMaxTreeType = typename SuperClass::DummyMinMaxTreeType; \
\
    using SuperClass::tree; \
    using SuperClass::constTree; \
\
    using SuperClass::makeLevelHeights; \
    using SuperClass::verifyNodeChain; \
\
    virtual void TestBody(); \
}

#endif
