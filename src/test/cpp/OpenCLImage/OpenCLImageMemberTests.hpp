#ifndef OPEN_C_L_IMAGE_MEMBER_TESTS_HPP
#define OPEN_C_L_IMAGE_MEMBER_TESTS_HPP

#include "OpenCLImageTest.hpp"

class OpenCLImageMemberTests : public OpenCLImageTest {
};

#define TEST_C(TestName) \
    TEST_F(OpenCLImageMemberTests, TestName)

#endif
