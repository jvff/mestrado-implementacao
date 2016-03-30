#ifndef BINARIZATION_FILTER_TEST_HPP
#define BINARIZATION_FILTER_TEST_HPP

#include <functional>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "BinarizationFilter.hpp"
#include "SimpleArrayImage.hpp"

#include "../DummyTypes.hpp"
#include "../FakeImage.hpp"

#define TEST_C(testCase, testName) \
        TEST(BinarizationFilter##testCase, testName)

template <typename T>
class EqualsComparator {
public:
    bool operator() (const T& first, const T& second) {
        return first == second;
    }
};

#endif
