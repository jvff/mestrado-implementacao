#ifndef MAX_TREE_LEVEL_HPP
#define MAX_TREE_LEVEL_HPP

#include <memory>

#include "MaxTreeNode.hpp"

template <typename T>
class MaxTreeLevel {
private:
    using NodeType = MaxTreeNode<T>;
    using NodePointer = std::shared_ptr<NodeType>;

    bool empty = true;
    T level;
    unsigned int numberOfNodes = 0u;

public:
    MaxTreeLevel(const T& level) : level(level) {
    }

    bool isEmpty() {
        return empty;
    }

    NodePointer addNode() {
        auto node = std::make_shared<NodeType>(level, numberOfNodes);

        empty = false;
        ++numberOfNodes;

        return node;
    }
};

#endif
