#ifndef COMPARISON_TESTS_HPP
#define COMPARISON_TESTS_HPP

#include "ImplementationTestMacros.hpp"

IMAGE_IMPLEMENTATION_TEST_CASE(ImageImplementationComparisonTests);

#define TEST_C(testName) \
    IMAGE_IMPLEMENTATION_TEST(ImageImplementationComparisonTests, testName)

#endif
