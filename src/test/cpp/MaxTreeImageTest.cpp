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
