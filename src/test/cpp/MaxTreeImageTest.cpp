#include "MaxTreeImageTest.hpp"

TEST_F(MaxTreeImageTest, classTemplateExists) {
    AssertThat<DummyMaxTreeImageType>::isClassOrStruct();
}

TEST_F(MaxTreeImageTest, isImage) {
    using ParentImageClass = Image<PixelType>;

    AssertThat<DummyMaxTreeImageType>::isSubClass(Of<ParentImageClass>());
}

TEST_F(MaxTreeImageTest, isConstructible) {
    using WidthParameter = unsigned int;
    using HeightParameter = unsigned int;

    AssertThat<DummyMaxTreeImageType>::isConstructible(With<WidthParameter,
            HeightParameter>());
}

TEST_F(MaxTreeImageTest, setsDimensions) {
    unsigned int width = 7539;
    unsigned int height = 401;

    DummyMaxTreeImageType image(width, height);

    assertThat(image.getWidth()).isEqualTo(width);
    assertThat(image.getHeight()).isEqualTo(height);
}

TEST_F(MaxTreeImageTest, updatesInternalImage) {
    unsigned int width = 6;
    unsigned int height = 4;

    DummyMaxTreeImageType image(width, height);

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y)
            image.setPixel(x, y, PixelType{ (int)(x + y * width) });
    }

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto pixelValue = image.getPixelValue(x, y);
            auto expectedPixelValue = PixelType{ (int)(x + y * width) };

            assertThat(pixelValue).isEqualTo(expectedPixelValue);
        }
    }
}
