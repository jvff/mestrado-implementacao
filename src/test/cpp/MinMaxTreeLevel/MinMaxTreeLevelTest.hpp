#ifndef MIN_MAX_TREE_LEVEL_TEST_HPP
#define MIN_MAX_TREE_LEVEL_TEST_HPP

#include <functional>
#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeLevel.hpp"

#include "../CustomTypedTestMacros.hpp"
#include "../DummyTypes.hpp"
#include "../NodeVerificationHelper.hpp"

template <typename TypeParameter>
class MinMaxTreeLevelTest : public ::testing::Test,
        public NodeVerificationHelper<DummyType, TypeParameter> {
protected:
    using LevelOrderComparator = TypeParameter;
    using DummyMinMaxTreeLevel = MinMaxTreeLevel<DummyType,
            LevelOrderComparator>;
    using NodeType = MinMaxTreeNode<DummyType, LevelOrderComparator>;
    using NodePointer = std::shared_ptr<NodeType>;
    using NodeVerificationHelperType = NodeVerificationHelper<DummyType,
            LevelOrderComparator>;

    DummyType levelHeight;
    DummyMinMaxTreeLevel level;
    const DummyMinMaxTreeLevel& constLevel;

public:
    MinMaxTreeLevelTest() : levelHeight(DummyType{ 201 }), level(levelHeight),
            constLevel(level) {
    }

protected:
    template <typename... RemainingParameters>
    void verifyNode(NodePointer nodePointer, unsigned int id,
            const RemainingParameters&... remainingParameters) {
        verifyNode(*nodePointer, levelHeight, id, remainingParameters...);
    }

    template <typename... RemainingParameters>
    void verifyNode(const NodeType& node, unsigned int id,
            const RemainingParameters&... remainingParameters) {
        verifyNode(node, levelHeight, id, remainingParameters...);
    }

protected:
    using NodeVerificationHelperType::verifyNode;
    using NodeVerificationHelperType::verifyNodeData;
};

#define TEST_C(testName) \
    CREATE_MIN_MAX_TREE_LEVEL_TEST_CLASS(testName); \
    REGISTER_CUSTOM_TYPED_TEST(MinMaxTreeLevelTest, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MinMaxTreeLevelTest, testName)

#define CREATE_MIN_MAX_TREE_LEVEL_TEST_CLASS(testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(MinMaxTreeLevelTest, testName) \
        : public MinMaxTreeLevelTest<TypeParameter> { \
private: \
    using SuperClass = MinMaxTreeLevelTest<TypeParameter>; \
    using DummyMinMaxTreeLevel = typename SuperClass::DummyMinMaxTreeLevel; \
    using NodeType = typename SuperClass::NodeType; \
\
    using SuperClass::levelHeight; \
    using SuperClass::level; \
    using SuperClass::constLevel; \
\
    using SuperClass::makeNode; \
    using SuperClass::verifyNode; \
\
    virtual void TestBody(); \
}

#endif
