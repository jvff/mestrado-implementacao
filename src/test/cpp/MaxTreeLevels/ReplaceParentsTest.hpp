#ifndef REPLACE_PARENTS_TEST_HPP
#define REPLACE_PARENTS_TEST_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include "MaxTreeLevel.hpp"
#include "MaxTreeNode.hpp"

#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(ReplaceParentsTest);

#undef CUSTOM_SUB_TEST_ADDITIONAL_MEMBERS
#define CUSTOM_SUB_TEST_ADDITIONAL_MEMBERS \
    using NodeType = MinMaxTreeNode<DummyType, LevelOrderComparator>; \
    using NodePointer = std::shared_ptr<NodeType>; \
\
    std::vector<DummyType> makeLevelHeights( \
            std::initializer_list<int> heights) { \
        std::vector<DummyType> heightsToSort; \
\
        for (auto height : heights) \
            heightsToSort.push_back(DummyType{ height }); \
\
        return sortHeights(heightsToSort); \
    } \
\
    std::vector<DummyType> sortHeights(std::vector<DummyType> heights) { \
        LevelOrderComparator comparator; \
\
        std::sort(heights.begin(), heights.end(), comparator); \
\
        return heights; \
    } \
\
    NodePointer makeNode(const DummyType& levelHeight, unsigned int id) { \
        return std::make_shared<NodeType>(levelHeight, id); \
    } \
\
    void createRootLevel(const DummyType& levelHeight) { \
        auto& level = levels.getOrCreateLevel(levelHeight); \
\
        level.addNode(); \
    } \
\
    template <typename... RemainingParameterTypes> \
    void createLevelWithParents(const DummyType& levelHeight, \
            RemainingParameterTypes... remainingParameters) { \
        auto& level = levels.getOrCreateLevel(levelHeight); \
\
        addNodesToLevel(level, remainingParameters...); \
    } \
\
    template <typename... RemainingParameterTypes> \
    void verifyTree(const DummyType& rootLevelHeight, \
            const RemainingParameterTypes&... remainingParameters) { \
        auto& firstLevel = levels.getFirstLevel(); \
\
        assertThat(firstLevel.getLevel()).isEqualTo(rootLevelHeight); \
        assertThat(firstLevel.hasNode(0u)).isEqualTo(true); \
        assertThat(firstLevel.hasNode(1u)).isEqualTo(false); \
        assertThat(firstLevel.getNode(0u)->hasParent()).isEqualTo(false); \
\
        verifyLevels(firstLevel, 1u, remainingParameters...); \
    } \
\
    template <typename... RemainingParameterTypes> \
    void addNodesToLevel(NodeLevel& level, const DummyType& parentLevel, \
            unsigned int parentId, \
            RemainingParameterTypes... remainingParameters) { \
        addNodesToLevel(level, parentLevel, parentId); \
        addNodesToLevel(level, remainingParameters...); \
    } \
\
    void addNodesToLevel(NodeLevel& level, const DummyType& parentLevel, \
            unsigned int parentId) { \
        auto newNode = level.addNode(); \
        auto parentNode = getNode(parentLevel, parentId); \
\
        newNode->setParent(parentNode); \
    } \
\
    NodePointer getNode(const DummyType& levelHeight, unsigned int id) { \
        auto& level = levels.getLevel(levelHeight); \
\
        return level.getNode(id); \
    } \
\
    template <typename... RemainingParameterTypes> \
    void verifyLevels(NodeLevel& previousLevel, unsigned int nodeId, \
            const DummyType& nextLevelHeight, \
            const DummyType& nextParentLevelHeight, \
            const RemainingParameterTypes&... remainingParameters) { \
        auto& nextLevel = levels.getLevel(nextLevelHeight); \
\
        assertThat(previousLevel.hasNode(nodeId - 1u)).isEqualTo(true); \
        assertThat(previousLevel.hasNode(nodeId)).isEqualTo(false); \
        assertThat(nextLevel.getLevel()).isEqualTo(nextLevelHeight); \
\
        verifyLevels(nextLevel, 0u, nextParentLevelHeight, \
                remainingParameters...); \
    } \
\
    template <typename... RemainingParameterTypes> \
    void verifyLevels(NodeLevel& level, unsigned int nodeId, \
            const DummyType& parentLevelHeight, unsigned int parentNodeId, \
            const RemainingParameterTypes&... remainingParameters) { \
        auto nodePointer = level.getNode(nodeId); \
        auto& parentNode = nodePointer->getParent(); \
        auto& parentLevel = levels.getLevel(parentLevelHeight); \
        auto expectedParentNodePointer = parentLevel.getNode(parentNodeId); \
\
        assertThat(nodePointer->getId()).isEqualTo(nodeId); \
        assertThat(nodePointer->getLevel()).isEqualTo(level.getLevel()); \
        assertThat(parentNode.getId()).isEqualTo(parentNodeId); \
        assertThat(parentNode.getLevel()).isEqualTo(parentLevelHeight); \
        assertThat(parentNode).isAtSameAddressAs(*expectedParentNodePointer); \
\
        verifyLevels(level, nodeId + 1, remainingParameters...); \
    } \
\
    void verifyLevels(NodeLevel& lastLevel, unsigned int nodeId) { \
        assertThat(lastLevel.hasNode(nodeId - 1u)).isEqualTo(true); \
        assertThat(lastLevel.hasNode(nodeId)).isEqualTo(false); \
    }

#endif
