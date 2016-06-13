#ifndef RGB_IMAGE_BASIC_TESTS_HPP
#define RGB_IMAGE_BASIC_TESTS_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "../../FakeImage.hpp"

template <typename PixelTypeParameter>
class RgbImageBasicTests : public ::testing::Test {
protected:
    using PixelType = PixelTypeParameter;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageType = RgbImage<InternalImageType>;
};

#define TEST_C(TestName) \
    TYPED_TEST(RgbImageBasicTests, TestName)

#endif
