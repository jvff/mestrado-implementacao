#include "ImageFactoryTest.hpp"

TEST_F(ImageFactoryTest, classIsntAbstract) {
    EXPECT_TRUE(factory != NULL);
}

TEST_F(ImageFactoryTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    MockImageFactory<FakeImage<DummyType> >* mockFactory;
    ImageFactory<FakeImage<DummyType> >* factory;

    mockFactory = new MockImageFactory<FakeImage<DummyType> >();
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
