#ifndef MAX_TREE_LEVEL_TEST_HPP
#define MAX_TREE_LEVEL_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevel.hpp"

#include "DummyTypes.hpp"

class MaxTreeLevelTest : public ::testing::Test {
protected:
    using DummyMaxTreeLevel = MaxTreeLevel<DummyType>;
};

#endif
