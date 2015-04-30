#ifndef SIMPLE_ARRAY_IMAGE_TEST_HPP
#define SIMPLE_ARRAY_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "VirtualDestructorTest.hpp"

class SimpleArrayImageTest : public testing::Test,
        protected VirtualDestructorTest {
};

#endif
