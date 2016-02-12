#ifndef MIN_MAX_TREE_HPP
#define MIN_MAX_TREE_HPP

#include <map>
#include <memory>

#include "MaxTreeNode.hpp"
#include "MaxTreeLevel.hpp"
#include "MaxTreeLevels.hpp"

template <typename T, typename LevelOrderComparator>
class MinMaxTree {
private:
    using NodeType = MaxTreeNode<T>;
    using NodeLevel = MaxTreeLevel<T>;
    using NodePointer = std::shared_ptr<NodeType>;

    MaxTreeLevels<T> levels;

public:
    bool isEmpty() const {
        return levels.isEmpty();
    }

    unsigned int numberOfLevels() const {
        return levels.numberOfLevels();
    }

    T getFirstLevel() {
        return levels.getFirstLevelHeight();
    }

    bool hasLevel(const T& level) {
        return levels.hasLevel(level);
    }

    const MaxTreeNode<T>& addNode(const T& level) {
        auto& levelNodes = levels.getOrCreateLevel(level);
        auto newNode = levelNodes.addNode();

        if (level != getFirstLevel())
            updateParentOf(newNode);

        return *newNode;
    }

    const MaxTreeNode<T>& getNode(const T& level, unsigned int id) const {
        auto& nodeList = levels.getLevel(level);

        return nodeList.getNodeReference(id);
    }

    const MaxTreeNode<T>& getLatestNodeOnLevel(const T& level) const {
        auto& levelNodes = levels.getLevel(level);

        return levelNodes.getLatestNodeReference();
    }

    void setNodeParent(MaxTreeNode<T> nodeToChange, MaxTreeNode<T> newParent) {
        auto nodePointerToChange = getNodePointer(nodeToChange);
        auto newParentPointer = getNodePointer(newParent);

        nodePointerToChange->setParent(newParentPointer);
    }

    void removeNode(const T& level, unsigned int id) {
        if (level == getFirstLevel() && id == 0u)
            removeRootNode();
        else if (hasLevel(level)) {
            auto& levelNodes = levels.getLevel(level);

            if (levelNodes.hasNode(id))
                removeNormalNode(level, id, levelNodes);
        }
    }

private:
    NodePointer getNodePointer(const MaxTreeNode<T>& node) {
        auto& levelNodes = levels.getLevel(node.getLevel());

        return levelNodes.getNode(node.getId());
    }

    void updateParentOf(NodePointer node) {
        auto& nodeListOfLevelBelow = levels.findLevelBefore(node->getLevel());
        auto latestNodeAtLevelBelow = nodeListOfLevelBelow.getLatestNode();

        node->setParent(latestNodeAtLevelBelow);
    }

    void removeRootNode() {
        auto oldRootLevel = getFirstLevel();

        levels.removeLevel(oldRootLevel);

        if (!levels.isEmpty())
            createNewRootNode();
    }

    void createNewRootNode() {
        auto& newRootLevelNodes = levels.getFirstLevel();

        auto newRootNode = newRootLevelNodes.getNode(0u);
        auto mergedNodes = newRootLevelNodes.collapseNodes();

        removeParentFromRootNode(newRootNode);

        replaceMergedParents(mergedNodes, newRootNode);
    }

    void removeParentFromRootNode(NodePointer rootNode) {
        NodePointer noParent;

        rootNode->setParent(noParent);
    }

    void replaceMergedParents(const std::vector<NodePointer>& mergedNodes,
            NodePointer newNode) {
        for (auto& mergedNode : mergedNodes)
            levels.replaceParents(mergedNode, newNode);
    }

    void removeNormalNode(const T& level, unsigned int id,
            NodeLevel& levelNodes) {
        auto nodeToRemove = levelNodes.getNode(id);

        updateChildrenOfRemovedNode(nodeToRemove);
        levelNodes.removeNode(id);
        removeLevelIfEmpty(level, levelNodes);
    }

    void updateChildrenOfRemovedNode(NodePointer oldParent) {
        NodePointer newParent;

        if (oldParent->hasParent())
            newParent = getParentOf(oldParent);

        levels.replaceParents(oldParent, newParent);
    }

    NodePointer getParentOf(NodePointer child) {
        auto& parent = child->getParent();

        return getNodePointer(parent);
    }

    void removeLevelIfEmpty(const T& level, NodeLevel& levelNodes) {
        if (levelNodes.isEmpty())
            levels.removeLevel(level);
    }
};

#endif
