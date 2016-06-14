#ifndef RGB_IMAGE_BASIC_TESTS_HPP
#define RGB_IMAGE_BASIC_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "../../CustomTypedTestMacros.hpp"
#include "../../FakeImage.hpp"

template <typename PixelType>
class RgbImageBasicTests : public ::testing::Test {
};

#define TEST_C(TestName) \
    CREATE_RGB_IMAGE_BASIC_TESTS_CLASS(TestName); \
    REGISTER_CUSTOM_TYPED_TEST(RgbImageBasicTests, TestName); \
    START_CUSTOM_TYPED_TEST_BODY(RgbImageBasicTests, TestName)

#define CREATE_RGB_IMAGE_BASIC_TESTS_CLASS(TestName) \
template <typename PixelTypeParameter> \
class GTEST_TEST_CLASS_NAME_(RgbImageBasicTests, TestName) \
        : public RgbImageBasicTests<PixelTypeParameter> { \
private: \
    using PixelType = PixelTypeParameter; \
    using InternalImageType = FakeImage<PixelType>; \
    using RgbImageType = RgbImage<InternalImageType>; \
\
public: \
    void TestBody(); \
}

#endif
