#ifndef MAX_TREE_LEVELS_REPLACE_PARENTS_TEST_HPP
#define MAX_TREE_LEVELS_REPLACE_PARENTS_TEST_HPP

#include <functional>
#include <memory>

#include "MaxTreeLevel.hpp"
#include "MaxTreeNode.hpp"

#include "MinMaxTreeLevelsTest.hpp"

class MaxTreeLevelsReplaceParentsTest
        : public MinMaxTreeLevelsTest<std::less<DummyType> > {
protected:
    using NodeType = MaxTreeNode<DummyType>;
    using NodeLevel = MaxTreeLevel<DummyType>;
    using NodePointer = std::shared_ptr<NodeType>;

protected:
    NodePointer makeNode(const DummyType& levelHeight, unsigned int id) {
        return std::make_shared<NodeType>(levelHeight, id);
    }

    NodePointer getNode(const DummyType& levelHeight, unsigned int id) {
        auto& level = levels.getLevel(levelHeight);
        auto oldParent = level.getNode(id);

        return oldParent;
    }

    void createRootLevel(int levelHeight) {
        auto& level = levels.getOrCreateLevel(DummyType{ levelHeight });

        level.addNode();
    }

    template <typename... RemainingParameterTypes>
    void createLevelWithParents(int levelHeight,
            RemainingParameterTypes... remainingParameters) {
        auto& level = levels.getOrCreateLevel(DummyType{ levelHeight });

        addNodesToLevel(level, remainingParameters...);
    }

    template <typename... RemainingParameterTypes>
    void verifyTree(const DummyType& rootLevelHeight,
            const RemainingParameterTypes&... remainingParameters) {
        auto& firstLevel = levels.getFirstLevel();

        assertThat(firstLevel.getLevel()).isEqualTo(rootLevelHeight);
        assertThat(firstLevel.hasNode(0u)).isEqualTo(true);
        assertThat(firstLevel.hasNode(1u)).isEqualTo(false);
        assertThat(firstLevel.getNode(0u)->hasParent()).isEqualTo(false);

        verifyLevels(firstLevel, 1u, remainingParameters...);
    }

private:
    template <typename... RemainingParameterTypes>
    void addNodesToLevel(NodeLevel& level, int parentLevel,
            unsigned int parentId,
            RemainingParameterTypes... remainingParameters) {
        addNodesToLevel(level, parentLevel, parentId);
        addNodesToLevel(level, remainingParameters...);
    }

    void addNodesToLevel(NodeLevel& level, int parentLevel,
            unsigned int parentId) {
        auto newNode = level.addNode();
        auto parentNode = getNode(parentLevel, parentId);

        newNode->setParent(parentNode);
    }

    NodePointer getNode(int levelHeight, unsigned int id) {
        auto& level = levels.getLevel(DummyType{ levelHeight });

        return level.getNode(id);
    }

    template <typename... RemainingParameterTypes>
    void verifyLevels(NodeLevel& previousLevel, unsigned int nodeId,
            const DummyType& nextLevelHeight,
            const RemainingParameterTypes&... remainingParameters) {
        auto& nextLevel = levels.getLevel(nextLevelHeight);

        assertThat(previousLevel.hasNode(nodeId - 1u)).isEqualTo(true);
        assertThat(previousLevel.hasNode(nodeId)).isEqualTo(false);
        assertThat(nextLevel.getLevel()).isEqualTo(nextLevelHeight);

        verifyLevels(nextLevel, 0u, remainingParameters...);
    }

    template <typename... RemainingParameterTypes>
    void verifyLevels(NodeLevel& level, unsigned int nodeId,
            int parentLevelHeightValue, unsigned int parentNodeId,
            const RemainingParameterTypes&... remainingParameters) {
        auto parentLevelHeight = DummyType{ parentLevelHeightValue };
        auto nodePointer = level.getNode(nodeId);
        auto& parentNode = nodePointer->getParent();
        auto& parentLevel = levels.getLevel(parentLevelHeight);
        auto expectedParentNodePointer = parentLevel.getNode(parentNodeId);

        assertThat(nodePointer->getId()).isEqualTo(nodeId);
        assertThat(nodePointer->getLevel()).isEqualTo(level.getLevel());
        assertThat(parentNode.getId()).isEqualTo(parentNodeId);
        assertThat(parentNode.getLevel()).isEqualTo(parentLevelHeight);
        assertThat(parentNode).isAtSameAddressAs(*expectedParentNodePointer);

        verifyLevels(level, nodeId + 1, remainingParameters...);
    }

    void verifyLevels(NodeLevel& lastLevel, unsigned int nodeId) {
        assertThat(lastLevel.hasNode(nodeId - 1u)).isEqualTo(true);
        assertThat(lastLevel.hasNode(nodeId)).isEqualTo(false);
    }
};

#endif
