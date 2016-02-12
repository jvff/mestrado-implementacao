#ifndef MIN_MAX_TREE_LEVELS_TEST_HPP
#define MIN_MAX_TREE_LEVELS_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "MinMaxTreeLevels.hpp"

#include "../CustomTypedTestMacros.hpp"
#include "../DummyTypes.hpp"

template <typename TypeParameter>
class MinMaxTreeLevelsTest : public ::testing::Test {
protected:
    using LevelOrderComparator = TypeParameter;
    using DummyMinMaxTreeLevels = MinMaxTreeLevels<DummyType,
            LevelOrderComparator>;

    static constexpr int minimumLevel = std::numeric_limits<int>::min();
    static constexpr int maximumLevel = std::numeric_limits<int>::max();

    DummyMinMaxTreeLevels levels;
    const DummyMinMaxTreeLevels& constLevels;

protected:
    MinMaxTreeLevelsTest() : constLevels(levels) {
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

using levelComparatorTypes = ::testing::Types<std::less<DummyType>,
        std::greater<DummyType> >;

#define SUB_TEST(testFixture) \
    CREATE_MIN_MAX_TREE_LEVELS_TEST_FIXTURE(MinMaxTreeLevels##testFixture); \
    INSTANTIATE_MIN_MAX_TREE_LEVELS_TEST_FIXTURE(MinMaxTreeLevels##testFixture)

#define CREATE_MIN_MAX_TREE_LEVELS_TEST_FIXTURE(testFixture) \
template <typename TypeParameter> \
class testFixture : public MinMaxTreeLevelsTest<TypeParameter> { \
}

#define INSTANTIATE_MIN_MAX_TREE_LEVELS_TEST_FIXTURE(testFixture) \
    TYPED_TEST_CASE(testFixture, levelComparatorTypes)

#define TEST_C(testFixture, testName) \
    CREATE_MIN_MAX_TREE_LEVELS_TEST_CLASS(MinMaxTreeLevels##testFixture, \
            testName); \
    REGISTER_CUSTOM_TYPED_TEST(MinMaxTreeLevels##testFixture, testName); \
    START_CUSTOM_TYPED_TEST_BODY(MinMaxTreeLevels##testFixture, testName)

#define CREATE_MIN_MAX_TREE_LEVELS_TEST_CLASS(testFixture, testName) \
template <typename TypeParameter> \
class GTEST_TEST_CLASS_NAME_(testFixture, testName) \
        : public testFixture<TypeParameter> { \
private: \
    using SuperClass = testFixture<TypeParameter>; \
    using DummyMinMaxTreeLevels = typename SuperClass::DummyMinMaxTreeLevels; \
\
    using SuperClass::minimumLevel; \
    using SuperClass::maximumLevel; \
\
    using SuperClass::levels; \
    using SuperClass::constLevels; \
\
    using SuperClass::verifyIfHasLevels; \
    using SuperClass::verifyDoesNotHaveLevels; \
\
    virtual void TestBody(); \
}

#endif
