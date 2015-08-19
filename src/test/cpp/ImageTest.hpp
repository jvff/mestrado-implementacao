#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "asserts.hpp"

#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

using namespace fakeit;

class ImageTest : public testing::Test {
protected:
    using DummyImage = Image<DummyType>;
    using FakeDummyImage = FakeImage<DummyType>;
};

#endif
