#ifndef REMOVE_LEVELS_TEST_HPP
#define REMOVE_LEVELS_TEST_HPP

#include <algorithm>
#include <vector>

#include "MinMaxTreeLevelsTest.hpp"

SUB_TEST(RemoveLevelsTest);

#undef CUSTOM_SUB_TEST_ADDITIONAL_MEMBERS
#define CUSTOM_SUB_TEST_ADDITIONAL_MEMBERS \
    std::vector<DummyType> levelHeights; \
\
    void SetUp() override { \
        createLevel(DummyType{ 1 }); \
        createLevel(DummyType{ 2 }); \
        createLevel(DummyType{ 3 }); \
        createLevel(DummyType{ 4 }); \
        createLevel(DummyType{ 5 }); \
\
        sortLevelHeights(); \
    } \
\
    void createLevel(DummyType height) { \
        levelHeights.push_back(height); \
        levels.getOrCreateLevel(height); \
    } \
\
    void sortLevelHeights() { \
        LevelOrderComparator comparator; \
\
        std::sort(levelHeights.begin(), levelHeights.end(), comparator); \
    }

#endif
