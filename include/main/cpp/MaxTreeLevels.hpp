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
        return 0u;
    }

    bool hasLevel(const T&) const {
        return false;
    }

    NodeLevel& getOrCreateLevel(const T& levelHeight) {
        level = std::make_shared<NodeLevel>(levelHeight);

        return *level;
    }
};

#endif
