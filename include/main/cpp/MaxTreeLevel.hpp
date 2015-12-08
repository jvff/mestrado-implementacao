#ifndef MAX_TREE_LEVEL_HPP
#define MAX_TREE_LEVEL_HPP

#include <memory>

#include "MaxTreeNode.hpp"

template <typename T>
class MaxTreeLevel {
private:
    using NodeType = MaxTreeNode<T>;
    using NodePointer = std::shared_ptr<NodeType>;

    T level;
    unsigned int numberOfNodes = 0u;

public:
    MaxTreeLevel(const T& level) : level(level) {
    }

    bool isEmpty() {
        return numberOfNodes == 0u;
    }

    NodePointer addNode() {
        auto node = std::make_shared<NodeType>(level, numberOfNodes);

        ++numberOfNodes;

        return node;
    }

    NodePointer getNode(unsigned int id) {
        return std::make_shared<NodeType>(level, id);
    }
};

#endif
