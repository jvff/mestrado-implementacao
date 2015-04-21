#ifndef IMAGE_FACTORY_TEST_HPP
#define IMAGE_FACTORY_TEST_HPP

#include <gtest/gtest.h>

#include "ImageFactory.hpp"
#include "Image.hpp"

#include "DummyImageFactory.hpp"

class ImageFactoryTest : public testing::Test {
protected:
    DummyImageFactory* dummyFactory;
    DummyImage* image;
    ImageFactory<DummyImage>* factory;

    void SetUp() {
        dummyFactory = new DummyImageFactory();
        factory = dummyFactory;
        image = NULL;
    }

    void TearDown() {
        if (dummyFactory != NULL)
            delete dummyFactory;

        if (image != NULL)
            delete image;
    }

    void createImage(int width, int height) {
        image = factory->createImage(width, height);
    }
};

#endif
