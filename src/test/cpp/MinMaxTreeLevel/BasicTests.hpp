#ifndef BASIC_TESTS_HPP
#define BASIC_TESTS_HPP

#include "MinMaxTreeLevelTest.hpp"

template <typename LevelOrderComparator>
class MinMaxTreeLevelBasicTests
        : public MinMaxTreeLevelTest<LevelOrderComparator> {
};

#undef TEST_FIXTURE_NAME
#define TEST_FIXTURE_NAME MinMaxTreeLevelBasicTests

#endif
