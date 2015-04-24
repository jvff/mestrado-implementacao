#include "ImageFactoryTest.hpp"

TEST_F(ImageFactoryTest, classIsntAbstract) {
    EXPECT_TRUE(factory != NULL);
}

TEST_F(ImageFactoryTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    MockImageFactory<MockImage<DummyType> >* mockFactory;
    ImageFactory<MockImage<DummyType> >* factory;

    mockFactory = new MockImageFactory<MockImage<DummyType> >();
    mockFactory->setDestructorListener(&destructorWasCalled);

    factory = mockFactory;
    delete factory;

    EXPECT_TRUE(destructorWasCalled);
}

TEST_F(ImageFactoryTest, createdImageIsntNull) {
    createImage(1, 1);

    EXPECT_TRUE(image != NULL);
}

TEST_F(ImageFactoryTest, createdImageDimensionsAreCorrect) {
    int width = 15;
    int height = 10;

    createImage(width, height);

    ASSERT_TRUE(image != NULL);
    EXPECT_EQ(width, image->getWidth());
    EXPECT_EQ(height, image->getHeight());
}
