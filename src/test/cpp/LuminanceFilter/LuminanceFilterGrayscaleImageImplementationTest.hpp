#ifndef LUMINANCE_FILTER_GRAYSCALE_IMAGE_IMPLEMENTATION_TEST_HPP
#define LUMINANCE_FILTER_GRAYSCALE_IMAGE_IMPLEMENTATION_TEST_HPP

#include "LuminanceFilterImplementationTests.hpp"

LUMINANCE_FILTER_IMPLEMENTATION_TEST_CASE(
        LuminanceFilterGrayscaleImageImplementationTest);

#define TEST_C(testName) \
    TEST_C_FOR_TEST_CASE(LuminanceFilterGrayscaleImageImplementationTest, \
            testName)

#endif
