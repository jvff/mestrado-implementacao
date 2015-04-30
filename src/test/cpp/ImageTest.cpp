#include "ImageTest.hpp"

TEST_F(ImageTest, classIsntAbstract) {
    makeImage(0, 0);

    EXPECT_TRUE(image != NULL);
}

TEST_F(ImageTest, destructorIsVirtual) {
    testIfDestructorIsVirtual<DummyImage, FakeDummyImage, int, int>(0, 0);
}

TEST_F(ImageTest, widthIsCorrect) {
    int width = 100;

    makeImage(width, 1);

    EXPECT_EQ(width, image->getWidth());
}

TEST_F(ImageTest, heightIsCorrect) {
    int height = 100;

    makeImage(1, height);

    EXPECT_EQ(height, image->getHeight());
}

TEST_F(ImageTest, widthAndHeightAreCorrect) {
    int width = 35;
    int height = 63;

    makeImage(width, height);

    EXPECT_EQ(width, image->getWidth());
    EXPECT_EQ(height, image->getHeight());
}