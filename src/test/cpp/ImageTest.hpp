#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class ImageTest : public testing::Test {
protected:
    typedef Image<DummyType> DummyImage;
    typedef FakeImage<DummyType> FakeDummyImage;
};

#endif
