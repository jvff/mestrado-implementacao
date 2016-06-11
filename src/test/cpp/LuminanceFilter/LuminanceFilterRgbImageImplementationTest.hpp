#ifndef LUMINANCE_FILTER_RGB_IMAGE_IMPLEMENTATION_TEST_HPP
#define LUMINANCE_FILTER_RGB_IMAGE_IMPLEMENTATION_TEST_HPP

#include "LuminanceFilterImplementationTests.hpp"

LUMINANCE_FILTER_IMPLEMENTATION_TEST_CASE(
        LuminanceFilterRgbImageImplementationTest);

#define TEST_C(testName) \
    TEST_C_FOR_TEST_CASE(LuminanceFilterRgbImageImplementationTest, testName)

#endif
