#ifndef STORAGE_TESTS_HPP
#define STORAGE_TESTS_HPP

#include "ImplementationTestMacros.hpp"

IMAGE_IMPLEMENTATION_TEST_CASE(ImageImplementationStorageTests);

#define TEST_C(testName) \
    IMAGE_IMPLEMENTATION_TEST(ImageImplementationStorageTests, testName)

#endif
