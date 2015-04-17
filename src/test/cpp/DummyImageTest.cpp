#include <gtest/gtest.h>

#include "Image.hpp"

#include "DummyImage.hpp"

TEST(DummyImageTest, classIsntAbstract) {
    Image<DummyType>* image = new DummyImage(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}

TEST(DummyImageTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummyImage* dummyImage = new DummyImage(0, 0);
    Image<DummyType>* image = dummyImage;

    dummyImage->setDestructorListener(&destructorWasCalled);

    delete image;

    EXPECT_TRUE(destructorWasCalled);
}
