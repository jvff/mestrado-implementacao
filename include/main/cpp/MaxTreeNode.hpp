#ifndef MAX_TREE_NODE_HPP
#define MAX_TREE_NODE_HPP

#include <memory>

template <typename PixelType>
struct MaxTreeNode {
    std::shared_ptr<MaxTreeNode<PixelType> > parent;
    PixelType level;
    unsigned int id;

    MaxTreeNode() {
    }

    MaxTreeNode(const std::shared_ptr<MaxTreeNode<PixelType> >& parent,
            const PixelType& level, unsigned int id)
            : parent(parent), level(level), id(id) {
    }
};

#endif
