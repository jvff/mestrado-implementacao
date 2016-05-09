#ifndef OPEN_C_L_IMAGE_COMPARATOR_BASIC_TESTS_HPP
#define OPEN_C_L_IMAGE_COMPARATOR_BASIC_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "OpenCLFilter.hpp"
#include "OpenCLImageComparator.hpp"

#include "../DummyTypes.hpp"

class OpenCLImageComparatorBasicTests : public ::testing::Test {
protected:
    using ComparatorType = OpenCLImageComparator<DummyType>;
};

#define TEST_C(TestName) \
    TEST_F(OpenCLImageComparatorBasicTests, TestName)

#endif
