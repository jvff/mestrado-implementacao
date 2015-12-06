#ifndef MAX_TREE_NODE_HPP
#define MAX_TREE_NODE_HPP

#include <memory>

template <typename T>
class MaxTreeNode {
private:
    std::shared_ptr<MaxTreeNode<T> > parent;
    T level;
    unsigned int id;

public:
    MaxTreeNode() {
    }

    MaxTreeNode(const T& level, unsigned int id) : level(level), id(id) {
    }

    MaxTreeNode(const std::shared_ptr<MaxTreeNode<T> >& parent, const T& level,
            unsigned int id) : parent(parent), level(level), id(id) {
    }

    unsigned int getId() const {
        return id;
    }

    void setId(unsigned int newId) {
        id = newId;
    }

    T getLevel() const {
        return level;
    }

    void setLevel(const T& newLevel) {
        level = newLevel;
    }

    bool hasParent() const {
        return (bool)parent;
    }

    const MaxTreeNode<T>& getParent() const {
        return *parent;
    }

    void setParent(const std::shared_ptr<MaxTreeNode>& newParent) {
        parent = newParent;
    }
};

template <typename T>
bool operator==(const MaxTreeNode<T>& first, const MaxTreeNode<T>& second) {
    bool haveParents = first.hasParent() && second.hasParent();
    bool parentsAreEqual;

    if (haveParents)
        parentsAreEqual = &first.getParent() == &second.getParent();
    else
        parentsAreEqual = !first.hasParent() && !second.hasParent();

    return first.getLevel() == second.getLevel()
        && first.getId() == second.getId()
        && parentsAreEqual;
}

#endif
