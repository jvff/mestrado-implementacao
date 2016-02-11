#ifndef MAX_TREE_LEVELS_CREATE_THREE_LEVELS_TEST_HPP
#define MAX_TREE_LEVELS_CREATE_THREE_LEVELS_TEST_HPP

#include <functional>

#include "MinMaxTreeLevelsTest.hpp"

class MaxTreeLevelsCreateThreeLevelsTest
        : public MinMaxTreeLevelsTest<std::less<DummyType> > {
};

#endif
