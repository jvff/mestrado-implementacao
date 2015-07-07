#include "ImageTest.hpp"

TEST_F(ImageTest, classIsntAbstract) {
    AssertThat<FakeDummyImage>
            ::isConstructible(With<unsigned int, unsigned int>());
}

TEST_F(ImageTest, destructorIsVirtual) {
    AssertThat<DummyImage>::hasVirtualDestructor();
}

TEST_F(ImageTest, widthIsCorrect) {
    unsigned int width = 100;

    auto image = FakeDummyImage(width, 1);

    assertThat(image.getWidth()).isEqualTo(width);
}

TEST_F(ImageTest, heightIsCorrect) {
    unsigned int height = 100;

    auto image = FakeDummyImage(1, height);

    assertThat(image.getHeight()).isEqualTo(height);
}

TEST_F(ImageTest, widthAndHeightAreCorrect) {
    unsigned int width = 35;
    unsigned int height = 63;

    auto image = FakeDummyImage(width, height);

    assertThat(image.getWidth()).isEqualTo(width);
    assertThat(image.getHeight()).isEqualTo(height);
}

TEST_F(ImageTest, getWidthIsConstMethod) {
    assertThat(&DummyImage::getWidth).isConstMethod();
}

TEST_F(ImageTest, getHeightIsConstMethod) {
    assertThat(&DummyImage::getHeight).isConstMethod();
}
