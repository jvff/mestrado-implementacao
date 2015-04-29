#ifndef IMAGE_FACTORY_TEST_HPP
#define IMAGE_FACTORY_TEST_HPP

#include <gtest/gtest.h>

#include "ImageFactory.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class ImageFactoryTest : public testing::Test {
protected:
    ImageFactory<FakeImage<DummyType> >* factory;
    FakeImage<DummyType>* image;

    void SetUp() {
        factory = new ImageFactory<FakeImage<DummyType> >();
        image = NULL;
    }

    void TearDown() {
        if (factory != NULL)
            delete factory;

        if (image != NULL)
            delete image;
    }

    void createImage(int width, int height) {
        image = factory->createImage(width, height);
    }
};

#endif
