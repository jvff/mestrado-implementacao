#ifndef MIN_MAX_TREE_LEVEL_HPP
#define MIN_MAX_TREE_LEVEL_HPP

#include <memory>
#include <string>
#include <vector>

#include "MaxTreeNode.hpp"

template <typename T, typename LevelOrderComparator>
class MinMaxTreeLevel {
private:
    using NodeType = MinMaxTreeNode<T, LevelOrderComparator>;
    using NodePointer = std::shared_ptr<NodeType>;

    T levelHeight;
    std::vector<NodePointer> nodes;

public:
    MinMaxTreeLevel(const T& levelHeight) : levelHeight(levelHeight) {
    }

    T getLevel() const {
        return levelHeight;
    }

    bool isEmpty() {
        return nodes.empty();
    }

    bool hasNode(unsigned int id) const {
        return id < nodes.size();
    }

    NodePointer addNode() {
        auto node = std::make_shared<NodeType>(levelHeight, nodes.size());

        nodes.push_back(node);

        return node;
    }

    NodePointer getNode(unsigned int id) {
        if (id < nodes.size())
            return nodes[id];
        else
            throw std::string("Attempt to retrieve inexistent node");
    }

    const NodeType& getNodeReference(unsigned int id) const {
        if (id < nodes.size())
            return *nodes[id];
        else
            throw std::string("Attempt to retrieve inexistent node");
    }

    NodePointer getLatestNode() {
        return nodes.back();
    }

    const NodeType& getLatestNodeReference() const {
        return *nodes.back();
    }

    void removeNode(unsigned int id) {
        if (id < nodes.size())
            safelyRemoveNode(id);
    }

    void replaceParents(NodePointer oldParent, NodePointer newParent) {
        for (auto& node : nodes)
            maybeReplaceParent(node, oldParent, newParent);
    }

    std::vector<NodePointer> collapseNodes() {
        auto firstRemovedNode = nodes.begin() + 1;
        auto end = nodes.end();
        auto removedNodes = std::vector<NodePointer>(firstRemovedNode, end);

        nodes.erase(firstRemovedNode, end);

        return removedNodes;
    }

    bool operator==(const MinMaxTreeLevel& otherLevel) const {
        return heightIsTheSameOn(otherLevel) && nodesAreTheSameOn(otherLevel);
    }

private:
    void safelyRemoveNode(unsigned int id) {
        nodes.erase(nodes.begin() + id);

        updateNodeIds(id);
    }

    void updateNodeIds(unsigned int startId) {
        auto size = nodes.size();

        for (auto id = startId; id < size; ++id)
            nodes[id]->setId(id);
    }

    void maybeReplaceParent(NodePointer node, NodePointer oldParent,
            NodePointer newParent) {
        if (node->hasParent() && node->getParent() == *oldParent)
            node->setParent(newParent);
    }

    bool heightIsTheSameOn(const MinMaxTreeLevel& otherLevel) const {
        return otherLevel.levelHeight == levelHeight;
    }

    bool nodesAreTheSameOn(const MinMaxTreeLevel& otherLevel) const {
        auto numberOfNodes = nodes.size();

        if (otherLevel.nodes.size() != numberOfNodes)
            return false;

        for (auto index = 0u; index < numberOfNodes; ++index) {
            if (*otherLevel.nodes[index] != *nodes[index])
                return false;
        }

        return true;
    }
};

#endif
