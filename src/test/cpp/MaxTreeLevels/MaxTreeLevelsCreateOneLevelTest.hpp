#ifndef MAX_TREE_LEVELS_CREATE_ONE_LEVEL_TEST_HPP
#define MAX_TREE_LEVELS_CREATE_ONE_LEVEL_TEST_HPP

#include <functional>

#include "MinMaxTreeLevelsTest.hpp"

class MaxTreeLevelsCreateOneLevelTest
        : public MinMaxTreeLevelsTest<std::less<DummyType> > {
};

#endif
