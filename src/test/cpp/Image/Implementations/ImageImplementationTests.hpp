#ifndef IMAGE_IMPLEMENTATION_TESTS_HPP
#define IMAGE_IMPLEMENTATION_TESTS_HPP

#include <gtest/gtest.h>

#include "AbstractImageImplementationTest.hpp"
#include "ImplementationTestMacros.hpp"

IMAGE_IMPLEMENTATION_TEST_CASE(ImageImplementationTests);

#define TEST_C(testName) \
    IMAGE_IMPLEMENTATION_TEST(ImageImplementationTests, testName)

#endif
