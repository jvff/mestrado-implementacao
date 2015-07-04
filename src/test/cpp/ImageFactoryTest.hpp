#ifndef IMAGE_FACTORY_TEST_HPP
#define IMAGE_FACTORY_TEST_HPP

#include <memory>

#include <gtest/gtest.h>

#include "asserts.hpp"

#include "ImageFactory.hpp"
#include "Image.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

class ImageFactoryTest : public testing::Test {
protected:
    ImageFactory<FakeImage<DummyType> > factory;
    std::unique_ptr<FakeImage<DummyType> > image;

    void createImage(unsigned int width, unsigned int height) {
        image.reset(factory.createImage(width, height));
    }
};

#endif
