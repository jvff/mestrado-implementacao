#ifndef MAX_TREE_LEVELS_REMOVE_LEVELS_TEST_HPP
#define MAX_TREE_LEVELS_REMOVE_LEVELS_TEST_HPP

#include <functional>

#include "MinMaxTreeLevelsTest.hpp"

class MaxTreeLevelsRemoveLevelsTest
        : public MinMaxTreeLevelsTest<std::less<DummyType> > {
public:
    void SetUp() override {
        levels.getOrCreateLevel(DummyType{ 1 });
        levels.getOrCreateLevel(DummyType{ 2 });
        levels.getOrCreateLevel(DummyType{ 3 });
        levels.getOrCreateLevel(DummyType{ 4 });
        levels.getOrCreateLevel(DummyType{ 5 });
    }
};

#endif
