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

    MaxTreeNode(const PixelType& level, unsigned int id)
            : level(level), id(id) {
    }

    MaxTreeNode(const std::shared_ptr<MaxTreeNode<PixelType> >& parent,
            const PixelType& level, unsigned int id)
            : parent(parent), level(level), id(id) {
    }

    MaxTreeNode(const MaxTreeNode<PixelType>& copySource) {
        level = copySource.level;
        id = copySource.id;

        copyParentFrom(copySource);
    }

    unsigned int getId() {
        return id;
    }

    PixelType getLevel() {
        return level;
    }

    MaxTreeNode<PixelType> getParent() {
        return *parent;
    }

private:
    void copyParentFrom(const MaxTreeNode<PixelType>& copySource) {
        auto parentExists = (bool)copySource.parent;

        if (parentExists) {
            parent = std::make_shared<MaxTreeNode<PixelType> >(
                    *copySource.parent);
        }
    }
};

#endif
