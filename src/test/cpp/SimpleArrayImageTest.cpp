#include <gtest/gtest.h>

#include "DummySimpleArrayImage.hpp"

TEST(SimpleArrayImageTest, classIsntAbstract) {
    SimpleArrayImage<DummyType>* image = new DummySimpleArrayImage(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}

TEST(SimpleArrayImageTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummySimpleArrayImage* dummyImage = new DummySimpleArrayImage(0, 0);
    SimpleArrayImage<DummyType>* image = dummyImage;

    dummyImage->setDestructorListener(&destructorWasCalled);

    delete image;

    EXPECT_TRUE(destructorWasCalled);
}
