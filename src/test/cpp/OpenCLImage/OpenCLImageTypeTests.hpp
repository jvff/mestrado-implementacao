#ifndef OPEN_C_L_IMAGE_TYPE_TESTS_HPP
#define OPEN_C_L_IMAGE_TYPE_TESTS_HPP

#include "OpenCLPixelTypeData.hpp"

#include "FakeOpenCLImage.hpp"
#include "OpenCLImageTest.hpp"

class OpenCLImageTypeTests : public OpenCLImageTest {
};

#define TEST_C(TestName) \
    TEST_F(OpenCLImageTypeTests, TestName)

#endif
