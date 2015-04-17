#include <gtest/gtest.h>

#include "ImageFactory.hpp"
#include "Image.hpp"

#include "DummyImageFactory.hpp"

TEST(DummyImageFactoryTest, classIsntAbstract) {
    ImageFactory<DummyImage> *factory = new DummyImageFactory();

    EXPECT_TRUE(factory != NULL);

    delete factory;
}

TEST(DummyImageFactoryTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummyImageFactory* dummyFactory = new DummyImageFactory();
    ImageFactory<DummyImage>* factory = dummyFactory;

    dummyFactory->setDestructorListener(&destructorWasCalled);

    delete factory;

    EXPECT_TRUE(destructorWasCalled);
}

TEST(DummyImageFactoryTest, createdImageIsntNull) {
    ImageFactory<DummyImage>* factory = new DummyImageFactory();
    DummyImage* image = factory->createImage(1, 1);

    EXPECT_TRUE(image != NULL);

    delete factory;
    delete image;
}

TEST(DummyImageFactoryTest, createdImageDimensionsAreCorrect) {
    int width = 15;
    int height = 10;
    ImageFactory<DummyImage>* factory = new DummyImageFactory();
    DummyImage* image = factory->createImage(width, height);

    ASSERT_TRUE(image != NULL);
    EXPECT_EQ(width, image->getWidth());
    EXPECT_EQ(height, image->getHeight());

    delete factory;
    delete image;
}
