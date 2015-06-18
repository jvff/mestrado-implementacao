#include "ImageFactoryTest.hpp"

TEST_F(ImageFactoryTest, classIsntAbstract) {
    assertThat(factory).isNotNull();
}

TEST_F(ImageFactoryTest, destructorIsVirtual) {
    AssertThat<ImageFactory<FakeImage<DummyType> > >::hasVirtualDestructor();
}

TEST_F(ImageFactoryTest, createdImageIsntNull) {
    createImage(1, 1);

    assertThat(image).isNotNull();
}

TEST_F(ImageFactoryTest, createdImageDimensionsAreCorrect) {
    unsigned int width = 15;
    unsigned int height = 10;

    createImage(width, height);
    ASSERT_TRUE(image != NULL);

    assertThat(image->getWidth()).isEqualTo(width);
    assertThat(image->getHeight()).isEqualTo(height);
}
