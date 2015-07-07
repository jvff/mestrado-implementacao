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

TEST_F(ImageTest, isSettableWithLambdaExpression) {
    unsigned int width = 3;
    unsigned int height = 5;

    FakeDummyImage image(width, height);
    Mock<FakeDummyImage> spy(image);

    Spy(Method(spy, setPixel));

    image = [width] (unsigned int x, unsigned int y) -> DummyType {
        return DummyType{ (int)(y * width + x) };
    };

    DummyType pixelValue = {0};

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            Verify(Method(spy, setPixel).Using(x, y, pixelValue));

            ++pixelValue.value;
        }
    }
}
