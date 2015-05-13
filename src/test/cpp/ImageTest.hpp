#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "Image.hpp"

#include "VirtualDestructorTest.hpp"
#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class ImageTest : public testing::Test, protected VirtualDestructorTest {
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
