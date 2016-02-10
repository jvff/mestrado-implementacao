#ifndef MAX_TREE_LEVELS_CREATE_ONE_LEVEL_TEST_HPP
#define MAX_TREE_LEVELS_CREATE_ONE_LEVEL_TEST_HPP

#include <functional>

#include "MaxTreeLevelsTest.hpp"

class MaxTreeLevelsCreateOneLevelTest
        : public MaxTreeLevelsTest<std::less<DummyType> > {
};

#endif
