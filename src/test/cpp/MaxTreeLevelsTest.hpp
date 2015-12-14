#ifndef MAX_TREE_LEVELS_TEST_HPP
#define MAX_TREE_LEVELS_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevels.hpp"

#include "DummyTypes.hpp"

class MaxTreeLevelsTest : public ::testing::Test {
protected:
    using DummyMaxTreeLevels = MaxTreeLevels<DummyType>;

    DummyMaxTreeLevels levels;
    const DummyMaxTreeLevels& constLevels;

protected:
    MaxTreeLevelsTest() : constLevels(levels) {
    }
};

#endif
