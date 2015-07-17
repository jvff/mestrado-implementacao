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

TEST_F(ImageTest, getPixelIsConstMethod) {
    assertThat(&DummyImage::getPixel).isConstMethod();
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

TEST_F(ImageTest, imagesAreComparable) {
    unsigned int width = 2;
    unsigned int height = 9;

    FakeDummyImage firstImage(width, height);
    FakeDummyImage secondImage(width, height);

    assertThat(firstImage).isEqualTo(secondImage);
}

TEST_F(ImageTest, imagesWithDifferentWidthsArentEqual) {
    unsigned int firstWidth = 4;
    unsigned int secondWidth = 7;
    unsigned int height = 3;

    FakeDummyImage firstImage(firstWidth, height);
    FakeDummyImage secondImage(secondWidth, height);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(ImageTest, imagesWithDifferentHeightArentEqual) {
    unsigned int width = 3;
    unsigned int firstHeight = 4;
    unsigned int secondHeight = 7;

    FakeDummyImage firstImage(width, firstHeight);
    FakeDummyImage secondImage(width, secondHeight);

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(ImageTest, imagesWithDifferentPixelsAtZeroZeroArentEqual) {
    unsigned int width = 3;
    unsigned int height = 4;

    FakeDummyImage firstImage(width, height);
    FakeDummyImage secondImage(width, height);

    Mock<FakeDummyImage> firstImageSpy(firstImage);
    Mock<FakeDummyImage> secondImageSpy(secondImage);

    Spy(Method(firstImageSpy, getPixel));
    Spy(Method(secondImageSpy, getPixel));

    When(Method(firstImageSpy, getPixel).Using(0, 0)).Return(DummyType{ 1 });
    When(Method(secondImageSpy, getPixel).Using(0, 0)).Return(DummyType{ 2 });

    assertThat(firstImage).isNotEqualTo(secondImage);
}

TEST_F(ImageTest, imagesWithDifferentPixelsAtTwoThreeArentEqual) {
    unsigned int width = 3;
    unsigned int height = 4;

    FakeDummyImage firstImage(width, height);
    FakeDummyImage secondImage(width, height);

    Mock<FakeDummyImage> firstImageSpy(firstImage);
    Mock<FakeDummyImage> secondImageSpy(secondImage);

    Spy(Method(firstImageSpy, getPixel));
    Spy(Method(secondImageSpy, getPixel));

    When(Method(firstImageSpy, getPixel).Using(2, 3)).Return(DummyType{ 5 });
    When(Method(secondImageSpy, getPixel).Using(2, 3)).Return(DummyType{ 3 });

    assertThat(firstImage).isNotEqualTo(secondImage);
}
