#ifndef MAX_TREE_LEVELS_TEST_HPP
#define MAX_TREE_LEVELS_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MaxTreeLevels.hpp"

#include "../CustomTypedTestMacros.hpp"
#include "../DummyTypes.hpp"

template <typename TypeParameter>
class MaxTreeLevelsTest : public ::testing::Test {
protected:
    using LevelOrderComparator = TypeParameter;
    using DummyMinMaxTreeLevels = MinMaxTreeLevels<DummyType,
            LevelOrderComparator>;

    static constexpr int minimumLevel = std::numeric_limits<int>::min();
    static constexpr int maximumLevel = std::numeric_limits<int>::max();

    DummyMinMaxTreeLevels levels;
    const DummyMinMaxTreeLevels& constLevels;

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

#define TEST_C(testFixture, testName) \
    CREATE_MAX_TREE_LEVELS_TEST_CLASS(testFixture, testName); \
    REGISTER_CUSTOM_TYPED_TEST(testFixture, testName); \
    START_CUSTOM_TYPED_TEST_BODY(testFixture, testName)

#define CREATE_MAX_TREE_LEVELS_TEST_CLASS(testFixture, testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(testFixture, testName) \
        : public testFixture<TypeParameter> { \
private: \
    using SuperClass = testFixture<TypeParameter>; \
    using DummyMinMaxTreeLevels = typename SuperClass::DummyMinMaxTreeLevels; \
\
    using SuperClass::levels; \
    using SuperClass::constLevels; \
\
    virtual void TestBody(); \
}

#endif
