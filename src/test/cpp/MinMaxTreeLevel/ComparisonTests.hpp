#ifndef COMPARISON_TESTS_HPP
#define COMPARISON_TESTS_HPP

#include "MinMaxTreeLevelTest.hpp"

template <typename LevelOrderComparator>
class MinMaxTreeLevelComparisonTests
        : public MinMaxTreeLevelTest<LevelOrderComparator> {
};

#undef TEST_FIXTURE_NAME
#define TEST_FIXTURE_NAME MinMaxTreeLevelComparisonTests

#endif
