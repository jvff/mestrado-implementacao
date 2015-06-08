#include "ImageFactoryTest.hpp"

TEST_F(ImageFactoryTest, classIsntAbstract) {
    EXPECT_TRUE(factory != NULL);
}

TEST_F(ImageFactoryTest, destructorIsVirtual) {
    AssertThat<ImageFactory<FakeImage<DummyType> > >::hasVirtualDestructor();
}

TEST_F(ImageFactoryTest, createdImageIsntNull) {
    createImage(1, 1);

    EXPECT_TRUE(image != NULL);
}

TEST_F(ImageFactoryTest, createdImageDimensionsAreCorrect) {
    unsigned int width = 15;
    unsigned int height = 10;

    createImage(width, height);

    ASSERT_TRUE(image != NULL);
    EXPECT_EQ(width, image->getWidth());
    EXPECT_EQ(height, image->getHeight());
}
