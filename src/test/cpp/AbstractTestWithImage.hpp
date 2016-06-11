#ifndef ABSTRACT_TEST_WITH_IMAGE_HPP
#define ABSTRACT_TEST_WITH_IMAGE_HPP

#include <memory>

#include <gtest/gtest.h>

#include "TestImageFactory.hpp"

template <typename ImageType>
class AbstractTestWithImage : public ::testing::Test {
protected:
    static std::shared_ptr<TestImageFactory<ImageType> > imageFactory;

public:
    static void SetUpTestCase() {
        imageFactory.reset(new TestImageFactory<ImageType>());
    }

    static void TearDownTestCase() {
        imageFactory.reset();
    }

protected:
    ImageType createImage(unsigned int width, unsigned int height) {
        return imageFactory->createImage(width, height);
    }
};

template <typename ImageType>
std::shared_ptr<TestImageFactory<ImageType> >
        AbstractTestWithImage<ImageType>::imageFactory;

#endif
