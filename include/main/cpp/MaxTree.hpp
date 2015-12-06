#ifndef MAX_TREE_HPP
#define MAX_TREE_HPP

#include <map>
#include <memory>
#include <vector>

#include "MaxTreeNode.hpp"

template <typename T>
class MaxTree {
private:
    using NodeType = MaxTreeNode<T>;
    using NodePointer = std::shared_ptr<NodeType>;
    using NodeList = std::vector<NodePointer>;

    std::map<T, NodeList> levels;

public:
    bool isEmpty() const {
        return levels.empty();
    }

    unsigned int numberOfLevels() const {
        return levels.size();
    }

    void addNode(const T& level) {
        auto& levelNodes = getOrCreateLevel(level);
        auto newNodeId = levelNodes.size();
        auto newNode = makeNode(level, newNodeId);

        levelNodes.push_back(newNode);
    }

    MaxTreeNode<T> getNode(const T& level, unsigned int id) {
        auto nodePointer = getNodePointer(level, id);

        return *nodePointer;
    }

    MaxTreeNode<T> getLatestNodeOnLevel(const T& level) {
        auto& levelNodes = getLevel(level);
        auto nodePointer = levelNodes.back();

        return *nodePointer;
    }

    void setNodeParent(MaxTreeNode<T> nodeToChange, MaxTreeNode<T> newParent) {
        auto nodePointerToChange = getNodePointer(nodeToChange);
        auto newParentPointer = getNodePointer(newParent);

        nodePointerToChange->setParent(newParentPointer);
    }

    void removeNode(const T& level, unsigned int id) {
        if (levelExists(level)) {
            auto& levelNodes = getLevel(level);

            if (id < levelNodes.size())
                safelyRemoveNode(level, id, levelNodes);
        }
    }

private:
    NodePointer getNodePointer(const MaxTreeNode<T>& node) {
        return getNodePointer(node.getLevel(), node.getId());
    }

    NodePointer getNodePointer(const T& level, unsigned int id) {
        auto& nodeList = getLevel(level);

        return nodeList[id];
    }

    NodeList& getOrCreateLevel(const T& level) {
        if (!levelExists(level))
            createLevel(level);

        return getLevel(level);
    }

    NodeList& getLevel(const T& level) {
        return levels.at(level);
    }

    bool levelExists(const T& level) {
        const auto notFound = levels.end();
        auto searchResult = levels.find(level);

        return searchResult != notFound;
    }

    void createLevel(const T& level) {
        levels[level] = NodeList();
    }

    NodePointer makeNode(const T& level, unsigned int id) {
        auto node = std::make_shared<NodeType>(level, id);

        if (level != getFirstLevel())
            updateParentOf(node);

        return node;
    }

    T getFirstLevel() {
        auto firstPosition = levels.begin();
        auto firstLevel = firstPosition->first;

        return firstLevel;
    }

    void updateParentOf(NodePointer node) {
        auto& nodeListOfLevelBelow = findLevelBefore(node->getLevel());
        auto& latestNodeAtLevelBelow = nodeListOfLevelBelow.back();

        node->setParent(latestNodeAtLevelBelow);
    }

    NodeList& findLevelBefore(const T& level) {
        auto levelPosition = levels.find(level);

        --levelPosition;

        return levelPosition->second;
    }

    void safelyRemoveNode(const T& level, unsigned int id,
            NodeList& levelNodes) {
        auto nodeToRemove = levelNodes[id];

        updateChildrenOfRemovedNode(nodeToRemove);
        removeNodeFromLevel(id, levelNodes);
        updateNodeIds(id, levelNodes);
        removeLevelIfEmpty(level, levelNodes);
    }

    void removeNodeFromLevel(unsigned int id, NodeList& levelNodes) {
        levelNodes.erase(levelNodes.begin() + id);
    }

    void updateNodeIds(unsigned int startId, NodeList& levelNodes) {
        auto numberOfNodes = levelNodes.size();

        for (auto id = startId; id < numberOfNodes; ++id)
            levelNodes[id]->setId(id);
    }

    void updateChildrenOfRemovedNode(NodePointer oldParent) {
        NodePointer newParent;

        if (oldParent->hasParent())
            newParent = getParentOf(oldParent);

        replaceParents(oldParent, newParent);
    }

    NodePointer getParentOf(NodePointer child) {
        auto& parent = child->getParent();

        return getNodePointer(parent.getLevel(), parent.getId());
    }

    void replaceParents(NodePointer oldParent, NodePointer newParent) {
        auto startLevel = oldParent->getLevel();
        auto startPosition = levels.find(startLevel);
        auto endPosition = levels.end();

        for (auto position = startPosition; position != endPosition; ++position)
            replaceParentsInLevel(oldParent, newParent, position->second);
    }

    void replaceParentsInLevel(NodePointer oldParent, NodePointer newParent,
            NodeList& levelNodes) {
        for (auto& node : levelNodes) {
            if (node->hasParent() && getParentOf(node) == oldParent)
                node->setParent(newParent);
        }
    }

    void removeLevelIfEmpty(const T& level, NodeList& levelNodes) {
        if (levelNodes.size() == 0)
            levels.erase(level);
    }
};

#endif
