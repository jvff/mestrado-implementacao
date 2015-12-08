#ifndef MAX_TREE_LEVEL_HPP
#define MAX_TREE_LEVEL_HPP

#include <memory>
#include <vector>

#include "MaxTreeNode.hpp"

template <typename T>
class MaxTreeLevel {
private:
    using NodeType = MaxTreeNode<T>;
    using NodePointer = std::shared_ptr<NodeType>;

    T level;
    std::vector<NodePointer> nodes;

public:
    MaxTreeLevel(const T& level) : level(level) {
    }

    bool isEmpty() {
        return nodes.empty();
    }

    NodePointer addNode() {
        auto node = std::make_shared<NodeType>(level, nodes.size());

        nodes.push_back(node);

        return node;
    }

    NodePointer getNode(unsigned int id) {
        return nodes[id];
    }

    const NodeType& getNodeReference(unsigned int id) const {
        return *nodes[id];
    }

    NodePointer getLatestNode() {
        return nodes.back();
    }
};

#endif
