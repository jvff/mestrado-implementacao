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
