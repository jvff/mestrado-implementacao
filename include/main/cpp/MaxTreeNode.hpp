#ifndef MAX_TREE_NODE_HPP
#define MAX_TREE_NODE_HPP

#include <memory>

template <typename PixelType>
class MaxTreeNode {
private:
    std::shared_ptr<MaxTreeNode<PixelType> > parent;
    PixelType level;
    unsigned int id;

public:
    MaxTreeNode() {
    }

    MaxTreeNode(const PixelType& level, unsigned int id)
            : level(level), id(id) {
    }

    MaxTreeNode(const std::shared_ptr<MaxTreeNode<PixelType> >& parent,
            const PixelType& level, unsigned int id)
            : parent(parent), level(level), id(id) {
    }

    unsigned int getId() const {
        return id;
    }

    void setId(unsigned int newId) {
        id = newId;
    }

    PixelType getLevel() const {
        return level;
    }

    void setLevel(const PixelType& newLevel) {
        level = newLevel;
    }

    bool hasParent() const {
        return (bool)parent;
    }

    const MaxTreeNode<PixelType>& getParent() const {
        return *parent;
    }

    void setParent(const std::shared_ptr<MaxTreeNode>& newParent) {
        parent = newParent;
    }
};

#endif
