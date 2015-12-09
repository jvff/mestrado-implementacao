#ifndef MAX_TREE_HPP
#define MAX_TREE_HPP

#include <map>
#include <memory>

#include "MaxTreeNode.hpp"
#include "MaxTreeLevel.hpp"

template <typename T>
class MaxTree {
private:
    using NodeType = MaxTreeNode<T>;
    using NodeLevel = MaxTreeLevel<T>;
    using NodePointer = std::shared_ptr<NodeType>;

    std::map<T, NodeLevel> levels;

public:
    bool isEmpty() const {
        return levels.empty();
    }

    unsigned int numberOfLevels() const {
        return levels.size();
    }

    T getFirstLevel() {
        auto firstPosition = levels.begin();
        auto firstLevel = firstPosition->first;

        return firstLevel;
    }

    bool hasLevel(const T& level) {
        const auto notFound = levels.end();
        auto searchResult = levels.find(level);

        return searchResult != notFound;
    }

    const MaxTreeNode<T>& addNode(const T& level) {
        auto& levelNodes = getOrCreateLevel(level);
        auto newNode = levelNodes.addNode();

        if (level != getFirstLevel())
            updateParentOf(newNode);

        return *newNode;
    }

    const MaxTreeNode<T>& getNode(const T& level, unsigned int id) const {
        auto& nodeList = getLevel(level);

        return nodeList.getNodeReference(id);
    }

    const MaxTreeNode<T>& getLatestNodeOnLevel(const T& level) const {
        auto& levelNodes = getLevel(level);

        return levelNodes.getLatestNodeReference();
    }

    void setNodeParent(MaxTreeNode<T> nodeToChange, MaxTreeNode<T> newParent) {
        auto nodePointerToChange = getNodePointer(nodeToChange);
        auto newParentPointer = getNodePointer(newParent);

        nodePointerToChange->setParent(newParentPointer);
    }

    void removeNode(const T& level, unsigned int id) {
        if (hasLevel(level)) {
            auto& levelNodes = getLevel(level);

            if (levelNodes.hasNode(id))
                safelyRemoveNode(level, id, levelNodes);
        }
    }

private:
    NodePointer getNodePointer(const MaxTreeNode<T>& node) {
        auto& levelNodes = getLevel(node.getLevel());

        return levelNodes.getNode(node.getId());
    }

    NodeLevel& getOrCreateLevel(const T& level) {
        if (!hasLevel(level))
            createLevel(level);

        return getLevel(level);
    }

    const NodeLevel& getLevel(const T& level) const {
        return levels.at(level);
    }

    NodeLevel& getLevel(const T& level) {
        return levels.at(level);
    }

    void createLevel(const T& level) {
        levels.emplace(level, NodeLevel(level));
    }

    void updateParentOf(NodePointer node) {
        auto& nodeListOfLevelBelow = findLevelBefore(node->getLevel());
        auto latestNodeAtLevelBelow = nodeListOfLevelBelow.getLatestNode();

        node->setParent(latestNodeAtLevelBelow);
    }

    NodeLevel& findLevelBefore(const T& level) {
        auto levelPosition = levels.find(level);

        --levelPosition;

        return levelPosition->second;
    }

    void safelyRemoveNode(const T& level, unsigned int id,
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

        replaceParents(oldParent, newParent);
    }

    NodePointer getParentOf(NodePointer child) {
        auto& parent = child->getParent();

        return getNodePointer(parent);
    }

    void replaceParents(NodePointer oldParent, NodePointer newParent) {
        auto startLevel = oldParent->getLevel();
        auto start = levels.find(startLevel);
        auto end = levels.end();

        for (auto position = start; position != end; ++position) {
            auto levelNodes = position->second;

            levelNodes.replaceParents(oldParent, newParent);
        }
    }

    void removeLevelIfEmpty(const T& level, NodeLevel& levelNodes) {
        if (levelNodes.isEmpty())
            levels.erase(level);
    }
};

#endif
