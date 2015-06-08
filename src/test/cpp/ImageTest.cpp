#include "ImageTest.hpp"

TEST_F(ImageTest, classIsntAbstract) {
    makeImage(0, 0);

    EXPECT_TRUE(image != NULL);
}

TEST_F(ImageTest, destructorIsVirtual) {
    AssertThat<DummyImage>::hasVirtualDestructor();
}

TEST_F(ImageTest, widthIsCorrect) {
    unsigned int width = 100;

    makeImage(width, 1);

    EXPECT_EQ(width, image->getWidth());
}

TEST_F(ImageTest, heightIsCorrect) {
    unsigned int height = 100;

    makeImage(1, height);

    EXPECT_EQ(height, image->getHeight());
}

TEST_F(ImageTest, widthAndHeightAreCorrect) {
    unsigned int width = 35;
    unsigned int height = 63;

    makeImage(width, height);

    EXPECT_EQ(width, image->getWidth());
    EXPECT_EQ(height, image->getHeight());
}
