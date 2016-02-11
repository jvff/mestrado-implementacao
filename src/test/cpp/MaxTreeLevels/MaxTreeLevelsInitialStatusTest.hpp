#ifndef MAX_TREE_LEVELS_INITIAL_STATUS_TEST_HPP
#define MAX_TREE_LEVELS_INITIAL_STATUS_TEST_HPP

#include <functional>

#include "MinMaxTreeLevelsTest.hpp"

class MaxTreeLevelsInitialStatusTest
        : public MinMaxTreeLevelsTest<std::less<DummyType> > {
};

#endif
