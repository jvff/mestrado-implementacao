#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class ImageTest : public testing::Test {
protected:
    Image<DummyType>* image;
    FakeImage<DummyType>* mockImage;

    void SetUp() {
        image = NULL;
        mockImage = NULL;
    }

    void TearDown() {
        if (mockImage != NULL)
            delete mockImage;
    }

    void makeImage(int width, int height) {
        mockImage = new FakeImage<DummyType>(width, height);
        image = mockImage;
    }
};

#endif
