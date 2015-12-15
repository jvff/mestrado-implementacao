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

    void verifyIfHasLevels(int level) {
        assertThat(constLevels.hasLevel(DummyType{ level })).isEqualTo(true);
    }

    template <typename... RemainingLevelTypes>
    void verifyIfHasLevels(int level, RemainingLevelTypes... remainingLevels) {
        verifyIfHasLevels(level);
        verifyIfHasLevels(remainingLevels...);
    }

    void verifyDoesNotHaveLevels(int level) {
        assertThat(constLevels.hasLevel(DummyType{ level })).isEqualTo(false);
    }

    template <typename... RemainingLevelTypes>
    void verifyDoesNotHaveLevels(int level,
            RemainingLevelTypes... remainingLevels) {
        verifyDoesNotHaveLevels(level);
        verifyDoesNotHaveLevels(remainingLevels...);
    }
};

#endif
