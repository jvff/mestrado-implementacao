#ifndef MAX_TREE_HPP
#define MAX_TREE_HPP

#include <map>

#include "MaxTreeNode.hpp"

template <typename T>
class MaxTree {
private:
    std::map<T, unsigned int> levels;

public:
    bool isEmpty() {
        return levels.empty();
    }

    unsigned int numberOfLevels() {
        return levels.size();
    }

    void addNode(const T& level) {
        auto& levelNodes = getOrCreateLevel(level);

        ++levelNodes;
    }

    MaxTreeNode<T> getNode(const T& level, unsigned int id) {
        MaxTreeNode<T> node;

        node.level = level;
        node.id = id;

        return node;
    }

    void removeNode(const T& level, unsigned int) {
        if (!levelExists(level))
            return;

        auto& levelNodes = getLevel(level);

        --levelNodes;

        if (levelNodes == 0)
            levels.erase(level);
    }

private:
    unsigned int& getOrCreateLevel(const T& level) {
        if (!levelExists(level))
            createLevel(level);

        return getLevel(level);
    }

    unsigned int& getLevel(const T& level) {
        return levels.at(level);
    }

    bool levelExists(const T& level) {
        const auto notFound = levels.end();
        auto searchResult = levels.find(level);

        return searchResult != notFound;
    }

    void createLevel(const T& level) {
        levels[level] = 0u;
    }
};

#endif
