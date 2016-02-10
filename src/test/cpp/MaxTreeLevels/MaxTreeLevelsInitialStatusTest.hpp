#ifndef MAX_TREE_LEVELS_INITIAL_STATUS_TEST_HPP
#define MAX_TREE_LEVELS_INITIAL_STATUS_TEST_HPP

#include <functional>

#include "MaxTreeLevelsTest.hpp"

class MaxTreeLevelsInitialStatusTest
        : public MaxTreeLevelsTest<std::less<DummyType> > {
};

#endif
