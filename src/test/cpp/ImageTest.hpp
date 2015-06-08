#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class ImageTest : public testing::Test {
protected:
    typedef Image<DummyType> DummyImage;
    typedef FakeImage<DummyType> FakeDummyImage;

    DummyImage* image;
    FakeDummyImage* mockImage;

    void SetUp() {
        image = NULL;
        mockImage = NULL;
    }

    void TearDown() {
        if (mockImage != NULL)
            delete mockImage;
    }

    void makeImage(unsigned int width, unsigned int height) {
        mockImage = new FakeDummyImage(width, height);
        image = mockImage;
    }
};

#endif
