#ifndef RGB_IMAGE_TEST_HPP
#define RGB_IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "RgbImage.hpp"

#include "FakeImage.hpp"

class RgbImageTest : public ::testing::Test {
protected:
    using PixelType = unsigned int;
    using InternalImageType = FakeImage<PixelType>;
    using RgbImageType = RgbImage<InternalImageType>;
};

#endif
