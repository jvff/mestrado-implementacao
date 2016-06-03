#ifndef DIFFERENT_PIXELS_TEST_HPP
#define DIFFERENT_PIXELS_TEST_HPP

#include "ImplementationTestMacros.hpp"

IMAGE_IMPLEMENTATION_TEST_CASE(ImageImplementationDifferentPixelsTests);

#define TEST_C(testName) \
    IMAGE_IMPLEMENTATION_TEST_WITH_PATTERN_PAIR( \
            ImageImplementationDifferentPixelsTests, testName)

#endif
