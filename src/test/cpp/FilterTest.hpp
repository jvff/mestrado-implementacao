#ifndef FILTER_TEST_HPP
#define FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "VirtualDestructorTest.hpp"

class FilterTest : public testing::Test,
        protected VirtualDestructorTest {
};

#endif
