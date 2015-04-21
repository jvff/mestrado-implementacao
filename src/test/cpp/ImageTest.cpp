#include <gtest/gtest.h>

#include "Image.hpp"

#include "DummyImage.hpp"

TEST(ImageTest, classIsntAbstract) {
    Image<DummyType>* image = new DummyImage(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}

TEST(ImageTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummyImage* dummyImage = new DummyImage(0, 0);
    Image<DummyType>* image = dummyImage;

    dummyImage->setDestructorListener(&destructorWasCalled);

    delete image;

    EXPECT_TRUE(destructorWasCalled);
}

TEST(ImageTest, widthIsCorrect) {
    int width = 100;
    Image<DummyType>* image = new DummyImage(width, 1);

    EXPECT_EQ(width, image->getWidth());

    delete image;
}

TEST(ImageTest, heightIsCorrect) {
    int height = 100;
    Image<DummyType>* image = new DummyImage(1, height);

    EXPECT_EQ(height, image->getHeight());

    delete image;
}

TEST(ImageTest, widthAndHeightAreCorrect) {
    int width = 35;
    int height = 63;
    Image<DummyType>* image = new DummyImage(width, height);

    EXPECT_EQ(width, image->getWidth());
    EXPECT_EQ(height, image->getHeight());

    delete image;
}
