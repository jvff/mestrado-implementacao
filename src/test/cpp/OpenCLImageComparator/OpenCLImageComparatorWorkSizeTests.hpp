#ifndef OPEN_C_L_IMAGE_COMPARATOR_WORK_SIZE_TESTS_HPP
#define OPEN_C_L_IMAGE_COMPARATOR_WORK_SIZE_TESTS_HPP

#include <string>

#include <CL/cl.hpp>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "fakeit.hpp"

#include "OpenCLImage.hpp"

#include "FakeOpenCLImageComparator.hpp"

#include "../DummyTypes.hpp"
#include "../NDRangeEqualsOperator.hpp"

using namespace fakeit;

class OpenCLImageComparatorWorkSizeTests : public ::testing::Test {
protected:
    template <typename PixelType>
    Mock<OpenCLImage<PixelType> > createMockImage(unsigned int width,
            unsigned int height) {
        auto mock = Mock<OpenCLImage<PixelType> >();

        When(Method(mock, getWidth)).Return(width);
        When(Method(mock, getHeight)).Return(height);

        return mock;
    }
};

#define TEST_C(TestName) \
    TEST_F(OpenCLImageComparatorWorkSizeTests, TestName)

#endif
