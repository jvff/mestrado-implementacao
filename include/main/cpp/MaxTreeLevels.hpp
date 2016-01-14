#ifndef MAX_TREE_LEVELS_HPP
#define MAX_TREE_LEVELS_HPP

#include <map>
#include <memory>

#include "MaxTreeLevel.hpp"

template <typename T>
class MaxTreeLevels {
private:
    using NodeLevel = MaxTreeLevel<T>;
    using NodePointer = std::shared_ptr<MaxTreeNode<T> >;

    std::map<T, NodeLevel> levels;

public:
    bool isEmpty() const {
        return levels.empty();
    }

    unsigned int numberOfLevels() const {
        return levels.size();
    }

    T getFirstLevelHeight() const {
        auto firstPosition = levels.begin();
        auto firstLevelHeight = firstPosition->first;

        return firstLevelHeight;
    }

    NodeLevel& getFirstLevel() {
        auto firstPosition = levels.begin();
        auto& firstLevel = firstPosition->second;

        return firstLevel;
    }

    bool hasLevel(const T& levelHeight) const {
        auto notFound = levels.end();
        auto searchResult = levels.find(levelHeight);

        return searchResult != notFound;
    }

    NodeLevel& getOrCreateLevel(const T& levelHeight) {
        if (!hasLevel(levelHeight))
            createLevel(levelHeight);

        return getLevel(levelHeight);
    }

    NodeLevel& getLevel(const T& levelHeight) {
        return levels.at(levelHeight);
    }

    const NodeLevel& getLevel(const T& levelHeight) const {
        return levels.at(levelHeight);
    }

    NodeLevel& findLevelBefore(const T& height) {
        auto firstPositionAfterOrAtHeight = levels.lower_bound(height);
        auto& positionBeforeHeight = firstPositionAfterOrAtHeight;

        --positionBeforeHeight;

        return positionBeforeHeight->second;;
    }

    void removeLevel(const T& height) {
        levels.erase(height);
    }

    void replaceParents(NodePointer oldParent, NodePointer newParent) {
        auto startLevelHeight = oldParent->getLevel();
        auto startLevel = levels.find(startLevelHeight);
        auto endLevel = levels.end();

        for (auto position = startLevel; position != endLevel; ++position) {
            auto& level = position->second;

            level.replaceParents(oldParent, newParent);
        }
    }

private:
    void createLevel(const T& levelHeight) {
        levels.emplace(levelHeight, NodeLevel(levelHeight));
    }
};

#endif
