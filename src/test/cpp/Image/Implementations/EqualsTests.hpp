#ifndef EQUALS_TESTS_HPP
#define EQUALS_TESTS_HPP

#include "ImplementationTestMacros.hpp"

IMAGE_IMPLEMENTATION_TEST_CASE(ImageImplementationEqualsTests);

#define TEST_C(testName) \
    IMAGE_IMPLEMENTATION_TEST(ImageImplementationEqualsTests, testName)

#endif
