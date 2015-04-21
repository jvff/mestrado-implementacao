#ifndef IMAGE_TEST_HPP
#define IMAGE_TEST_HPP

#include <gtest/gtest.h>

#include "Image.hpp"

#include "DummyImage.hpp"

class ImageTest : public testing::Test {
protected:
    Image<DummyType>* image;
    DummyImage* dummyImage;

    void SetUp() {
	image = NULL;
	dummyImage = NULL;
    }

    void TearDown() {
	if (dummyImage != NULL)
	    delete dummyImage;
    }

    void makeImage(int width, int height) {
	dummyImage = new DummyImage(width, height);
	image = dummyImage;
    }
};

#endif
