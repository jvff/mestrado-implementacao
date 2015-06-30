#include "ImageTest.hpp"

TEST_F(ImageTest, classIsntAbstract) {
    makeImage(0, 0);

    assertThat(image).isNotNull();
}

TEST_F(ImageTest, destructorIsVirtual) {
    AssertThat<DummyImage>::hasVirtualDestructor();
}

TEST_F(ImageTest, widthIsCorrect) {
    unsigned int width = 100;

    makeImage(width, 1);

    assertThat(image->getWidth()).isEqualTo(width);
}

TEST_F(ImageTest, heightIsCorrect) {
    unsigned int height = 100;

    makeImage(1, height);

    assertThat(image->getHeight()).isEqualTo(height);
}

TEST_F(ImageTest, widthAndHeightAreCorrect) {
    unsigned int width = 35;
    unsigned int height = 63;

    makeImage(width, height);

    assertThat(image->getWidth()).isEqualTo(width);
    assertThat(image->getHeight()).isEqualTo(height);
}

TEST_F(ImageTest, getWidthIsConstMethod) {
    assertThat(&DummyImage::getWidth).isConstMethod();
}

TEST_F(ImageTest, getHeightIsConstMethod) {
    assertThat(&DummyImage::getHeight).isConstMethod();
}
