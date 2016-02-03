#ifndef MIN_MAX_TREE_NODE_HPP
#define MIN_MAX_TREE_NODE_HPP

#include <memory>

template <typename T, typename LevelOrderComparator>
class MinMaxTreeNode {
private:
    using NodeType = MinMaxTreeNode<T, LevelOrderComparator>;

    std::shared_ptr<NodeType> parent;
    T level;
    unsigned int id;

public:
    MinMaxTreeNode() {
    }

    MinMaxTreeNode(const T& level, unsigned int id) : level(level), id(id) {
    }

    MinMaxTreeNode(const std::shared_ptr<NodeType>& parent, const T& level,
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

    const NodeType& getParent() const {
        return *parent;
    }

    void setParent(const std::shared_ptr<NodeType>& newParent) {
        parent = newParent;
    }

    bool isEquivalentTo(const NodeType& otherNode) const {
        if (*this == otherNode)
            return true;

        bool haveParents = hasParent() && otherNode.hasParent();
        bool parentsAreEquivalent;

        if (haveParents)
            parentsAreEquivalent = parent->isEquivalentTo(*otherNode.parent);
        else
            parentsAreEquivalent = !hasParent() && !otherNode.hasParent();

        return level == otherNode.level
            && id == otherNode.id
            && parentsAreEquivalent;
    }

    bool operator<(const NodeType& otherNode) const {
        LevelOrderComparator isBefore;

        if (isBefore(level, otherNode.level))
            return true;
        else if (level != otherNode.level)
            return false;
        else
            return id < otherNode.id;
    }

    bool operator>(const NodeType& otherNode) const {
        LevelOrderComparator isBefore;

        if (isBefore(otherNode.level, level))
            return true;
        else if (level != otherNode.level)
            return false;
        else
            return id > otherNode.id;
    }
};

template <typename T, typename C>
bool operator==(const MinMaxTreeNode<T, C>& first,
        const MinMaxTreeNode<T, C>& second) {
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
