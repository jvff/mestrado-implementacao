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

    std::unique_ptr<DummyImage> image;

    void makeImage(unsigned int width, unsigned int height) {
        image.reset(new FakeImage<DummyType>(width, height));
    }
};

#endif
