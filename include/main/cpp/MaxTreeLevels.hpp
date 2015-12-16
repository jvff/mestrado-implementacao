#ifndef MAX_TREE_LEVELS_HPP
#define MAX_TREE_LEVELS_HPP

#include <memory>

#include "MaxTreeLevel.hpp"

template <typename T>
class MaxTreeLevels {
private:
    using NodeLevel = MaxTreeLevel<T>;

    std::shared_ptr<NodeLevel> level;

public:
    bool isEmpty() const {
        return !(bool)level;
    }

    unsigned int numberOfLevels() const {
        if (isEmpty())
            return 0u;
        else
            return 1u;
    }

    T getFirstLevelHeight() const {
        return level->getLevel();
    }

    NodeLevel& getFirstLevel() {
        return *level;
    }

    bool hasLevel(const T& levelHeight) const {
        return !isEmpty() && level->getLevel() == levelHeight;
    }

    NodeLevel& getOrCreateLevel(const T& levelHeight) {
        if (isEmpty())
            createLevel(levelHeight);

        return getLevel(levelHeight);
    }

    NodeLevel& getLevel(const T&) {
        return *level;
    }

    const NodeLevel& getLevel(const T&) const {
        return *level;
    }

private:
    void createLevel(const T& levelHeight) {
        level = std::make_shared<NodeLevel>(levelHeight);
    }
};

#endif
